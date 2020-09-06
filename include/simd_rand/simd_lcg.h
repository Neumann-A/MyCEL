#pragma once
#include <immintrin.h>

//#include <iostream>
//#include <array>
#include <cstdint>
#include <type_traits>
#include <numeric>
#include <cstdlib>
#include <chrono>
#include <cmath>

#include "constants.h"
#include "definitions.h"


inline uint32_t unxorshift1(uint32_t x, uint8_t bits, uint8_t shift)
{
	if (2 * shift >= bits) {
		return x ^ (x >> shift);
	}
	uint32_t lowmask1 = (uint32_t(1U) << (bits - shift * 2)) - 1;
	uint32_t highmask1 = ~lowmask1;
	uint32_t top1 = x;
	uint32_t bottom1 = x & lowmask1;
	top1 ^= top1 >> shift;
	top1 &= highmask1;
	x = top1 | bottom1;
	uint32_t lowmask2 = (uint32_t(1U) << (bits - shift)) - 1;
	uint32_t bottom2 = x & lowmask2;
	bottom2 = unxorshift1(bottom2, bits - shift, shift);
	bottom2 &= lowmask1;
	return top1 | bottom2;
}

struct rxs_m_xs_mix {

	static uint32_t output1(uint32_t internal)
	{
		constexpr const uint8_t xtypebits = 32;
		constexpr const uint8_t bits = 32;
		constexpr const uint8_t opbits = 4;
		constexpr const uint8_t shift = bits - xtypebits;
		constexpr const uint8_t mask = (1 << opbits) - 1;
		const uint8_t rshift =
			opbits ? uint8_t(internal >> (bits - opbits))& mask : 0;
		internal ^= internal >> (opbits + rshift);
		internal *= mcg_constant_32::multiplier;
		uint32_t result = internal >> shift;
		result ^= result >> ((2U * xtypebits + 2U) / 3U);
		return result;
	}

	static uint32_t unoutput1(uint32_t internal)
	{
		constexpr uint8_t bits = 32;
		constexpr uint8_t opbits = 4;
		constexpr uint8_t mask = (1 << opbits) - 1;

		internal = unxorshift1(internal, bits, (2U * bits + 2U) / 3U);

		internal *= mcg_constant_32::unmultiplier;
		uint8_t rshift = opbits ? (internal >> (bits - opbits))& mask : 0;
		internal = unxorshift1(internal, bits, opbits + rshift);

		return internal;
	}
};

namespace array_simd_pcg {

	template<InstructionSet arch, typename regtype, typename outtype>
	inline PackedElements<arch, outtype, std::uint32_t> output_SIMD(PackedElements<arch, regtype, std::uint64_t> internal) {
		constexpr std::uint64_t bits = 64;
		constexpr std::uint64_t result_bits = 32;
		constexpr std::uint64_t sparebits = bits - result_bits;
		constexpr std::uint64_t opbits = 5;
		constexpr std::uint64_t topspare = opbits;
		constexpr std::uint64_t bottomspare = (sparebits - topspare);
		constexpr std::uint64_t xshift = ((topspare + result_bits) / 2);
		constexpr std::uint64_t count = (bits - opbits);

		using reg = PackedElements<arch, regtype, std::uint64_t>;
		using out = PackedElements<arch, outtype, std::uint32_t>;
		reg shift_i;
		shift_i.storage = set1_reg<regtype, std::uint64_t>(std::uint64_t(xshift));

		reg count1;
		count1.storage = set1_reg<regtype, std::uint64_t>(std::uint64_t(count));

		reg bs;
		bs.storage = set1_reg<regtype, std::uint64_t>(std::uint64_t(bottomspare));

		shift_i = internal >> shift_i;
		reg xsh_shift = shift_i ^ internal;

		reg rot = internal >> count1;

		reg res = xsh_shift >> bs;
		// array
		internal = xsh_shift;


		out result = extract_low32<regtype, outtype>(res);
		out rotate = extract_low32<regtype, outtype>(rot);

		return packed_rotate_right(result, rotate);
	}

	template <typename RNG, typename seedDev>
	inline auto create_Seeded_PRNG(seedDev& dev) {
		const unsigned int generator_count = RNG::num_generators;
		typename RNG::seed_type seed[generator_count];
		for (int i = 0; i < generator_count; i++) {
			seed[i] = dev();
		}
		RNG seededRNG(seed);
		return seededRNG;
	};



	template <unsigned int independent_generators = 32, std::uint16_t table_k = 1024, InstructionSet arch = InstructionSet::AVX2, std::uint16_t optimal_output = 32>
	class packed_PCG {


	public:
		constexpr static InstructionSet used_arch = ((independent_generators < 8 && arch == InstructionSet::AVX512) || arch == InstructionSet::AVX2) ? InstructionSet::AVX2 : InstructionSet::AVX512;
		constexpr static unsigned int num_generators = independent_generators;
		using seed_type = std::uint64_t;

	protected:
		constexpr static bool isAVX512 = used_arch == InstructionSet::AVX512;
		constexpr static bool isAVX2 = used_arch == InstructionSet::AVX2;

		std::uint64_t multiplier;
		std::uint64_t increment[independent_generators];
		std::uint64_t start_state[independent_generators];
		std::uint64_t input_seed[independent_generators];

		using RegInfo = RegisterInfo<used_arch>;

		using  packet_type = typename RegInfo::type;
		using  result_type = typename RegInfo::half_type;

	public:
		constexpr static auto packed_elements = RegInfo::template packed_elements_size<std::uint64_t>();
	private:
		constexpr static auto generator_count = (independent_generators < packed_elements) ? packed_elements : independent_generators;

		constexpr static auto table_length = table_k;
		constexpr static int  opt_output = optimal_output < generator_count ? generator_count : optimal_output;

		constexpr static int extractor_const[8] = { 0,1,2,3,4,5,6,7 };

		constexpr static int m = used_arch == InstructionSet::AVX512 ? 8 : 4;

		constexpr static auto no_reg_spill_elements = generator_count % packed_elements;
		constexpr static bool does_spill_reg = (no_reg_spill_elements != 0);
		constexpr static auto min_required_state_registers = generator_count / packed_elements + does_spill_reg;
		constexpr static auto optimal_internal_reg_number = std::lcm(packed_elements, generator_count);

		constexpr static auto optimal_internal_cache_size = (opt_output > optimal_internal_reg_number) ? opt_output / optimal_internal_reg_number * optimal_internal_reg_number : optimal_internal_reg_number;
		const static auto reg_advances = (!does_spill_reg) ? (opt_output / generator_count * generator_count) / packed_elements : optimal_internal_cache_size / packed_elements;
	public:
		constexpr static auto calulated_results_per_generator = does_spill_reg ? optimal_internal_cache_size / generator_count : (reg_advances * packed_elements) / generator_count;
	private:
		using Packed_state = PackedElements<used_arch, packet_type, uint64_t>;
		using Packed_result = PackedElements<used_arch, result_type, uint32_t>;

		//Packed_result res[min_required_state_registers];
		Packed_state	state[min_required_state_registers];
		Packed_state	inc[min_required_state_registers];
		Packed_state	mult;
		packet_type		reg_idx[min_required_state_registers];

		Packed_state	shuffle_inc[reg_advances];
		Packed_state	shuffle_mult[reg_advances];
		Packed_state	shuffle_idx[reg_advances];
		std::int64_t	s_idx[reg_advances][packed_elements];

		Packed_state	old_state[min_required_state_registers];

		std::uint32_t	table[independent_generators][table_k];

		Packed_state	cache[reg_advances];
		Packed_result	resu[reg_advances];

		using U = std::conditional_t<does_spill_reg, SpareElements, NoSpareElements>;

		constexpr static int unused_count = ((independent_generators % packed_elements) == 0) ? 0 : packed_elements - independent_generators % packed_elements;

		int last_state_idx = reg_advances - min_required_state_registers;




	public:

		packed_PCG() {

			multiplier = lcg_constant64::multiplier;
			for (int i = 0; i < independent_generators; i++) {
				increment[i] = lcg_constant64::increment;
				input_seed[i] = 0xcafef00dd15ea5e5ULL;
				start_state[i] = 0xcafef00dd15ea5e5ULL + increment[i];
			}
			mult = { set1_reg<packet_type,uint64_t>(multiplier) };

			init_packed_inc_array();
			init_packed_state_array();
			init_packed_shuffle_idx();
			init_shuffle();
			bump(state);
			self_init();
		}

		packed_PCG(std::uint64_t seed_in[independent_generators]) {

			multiplier = lcg_constant64::multiplier;

			mult = { set1_reg<packet_type,std::uint64_t>(multiplier) };

			for (int i = 0; i < independent_generators; i++) {
				increment[i] = lcg_constant64::increment;
				input_seed[i] = seed_in[i];
				start_state[i] = seed_in[i] + increment[i];
			}

			init_packed_inc_array();
			init_packed_state_array();
			init_packed_shuffle_idx();
			init_shuffle();
			bump(state);
			self_init();
		}
		// copy constructor
		template <unsigned int independent_generators, std::uint16_t table_k = 1024, InstructionSet arch = InstructionSet::AVX2, std::uint16_t optimal_output = 32>
		packed_PCG(const packed_PCG<independent_generators, table_k, arch, optimal_output>& rng);


		inline auto operator()() {
			return output<U>();
		};

		constexpr static int get_results_per_generator() {
			return calulated_results_per_generator;
		};

		constexpr static int get_Output_elems() {
			return reg_advances;
		}

		InstructionSet get_used_arch() {
			return used_arch;
		}

		constexpr static int get_generator_count() {
			return independent_generators;
		}

		constexpr static int get_table_k() {
			return table_k;
		}


		void table_init(std::uint32_t Init_tables[independent_generators][table_k]) {
			for (int j = 0; j < independent_generators; j++)
				for (int i = 0; i < table_k; i++) {
					table[j][i] = Init_tables[j][i];
				}
			init_packed_inc_array();
			init_packed_state_array();
			init_packed_shuffle_idx();
			init_shuffle();
			bump(state);
		}

		void seed(std::uint64_t seed_in[independent_generators]) {
			for (int i = 0; i < independent_generators; i++) {
				input_seed[i] = seed_in[i];
				start_state[i] = seed_in[i] + increment[i];
			}
			init_packed_inc_array();
			init_packed_state_array();
			init_packed_shuffle_idx();
			init_shuffle();
			bump(state);
			self_init();
		}
		void set_multiplier(std::uint64_t in_multiplier) {
			mult = { set1_reg<packet_type,std::uint64_t>(in_multiplier) };
		}

		void set_inc(std::uint64_t in_increment[independent_generators]) {
			for (int i = 0; i < independent_generators; i++) {
				increment[i] = in_increment[i];
			}
			init_packed_inc_array();
			init_shuffle();
		}


		inline void discard(int n) {
			for (int k = 0; k < n; k++) {
				bump(state);
			}
		}


	private:

		template<typename A>
		inline auto output() {};

		template<>
		inline auto output<SpareElements>() {
			for (int i = 0; i < min_required_state_registers - 1; i++) {
				cache[i] = state[i];
			}
			cache[min_required_state_registers - 1] = fill_reg(state[min_required_state_registers - 1], bump_s(cache[0], shuffle_mult[0], shuffle_inc[0]), unused_count);

			for (auto i = min_required_state_registers; i < reg_advances; i++) {
				cache[i].storage = rotate_r_epi64<used_arch>(blendv_epi64<used_arch>(cache[i - min_required_state_registers].storage, cache[i - min_required_state_registers + 1].storage, unused_count), unused_count);
				cache[i] = bump_s(cache[i], shuffle_mult[i], shuffle_inc[i]);
			}

			for (auto i = 0; i < reg_advances; i++) {
				resu[i] = output_SIMD<used_arch, packet_type, result_type>(cache[i]) ^ get_extended_values(cache[i], s_idx[i]);
			}

			for (auto i = 0; i < min_required_state_registers - 1; i++) {
				state[i] = { rotate_r_epi64<used_arch>(blendv_epi64<used_arch>(cache[last_state_idx + i].storage, cache[last_state_idx + i + 1].storage, unused_count), unused_count) };
				state[i] = bump_s(state[i], shuffle_mult[i], shuffle_inc[i]);
			}
			state[min_required_state_registers - 1].storage = rotate_r_epi64<used_arch>(cache[reg_advances - 1].storage, unused_count);
			state[min_required_state_registers - 1] = bump_s(state[min_required_state_registers - 1], shuffle_mult[min_required_state_registers - 1], shuffle_inc[min_required_state_registers - 1]);

			return resu;
		};

		template<>
		inline auto output<NoSpareElements>() {
			for (int j = 0; j < calulated_results_per_generator; j++) {
				for (int i = 0; i < min_required_state_registers; i++) {

					resu[j * min_required_state_registers + i] = output_SIMD<used_arch, packet_type, result_type>(state[i]) ^ get_extended_values(state[i], s_idx[i]);
					state[i] = bump_s(state[i], shuffle_mult[i], shuffle_inc[i]);
				}
			}
			return resu;
		};

		void init_packed_state_array() {
			if (used_arch == InstructionSet::AVX2) {
#if __AVX2__
				uint64_t last_elements[packed_elements];
				for (int i = 0; i < min_required_state_registers; i++) {
					if ((i + 1) * packed_elements > independent_generators) {

						int rest = (i + 1) * packed_elements - independent_generators;
						rest = packed_elements - rest;

						for (int k = 0; k < packed_elements; k++) {
							if (k < rest)
								last_elements[k] = start_state[i * packed_elements + k];
							else
								last_elements[k] = 0;
						}
						state[i] = { set_reg<packet_type, uint64_t>(last_elements[3], last_elements[2], last_elements[1], last_elements[0]) };
					}
					else
						state[i] = { set_reg<packet_type, uint64_t>(start_state[i * packed_elements + 3], start_state[i * packed_elements + 2], start_state[i * packed_elements + 1], start_state[i * packed_elements + 0]) };
				}
#endif
			}
			else if (used_arch == InstructionSet::AVX512)
			{
#ifdef SIMD_RNG_AVX512
				uint64_t last_elements[packed_elements];
				for (int i = 0; i < min_required_state_registers; i++) {
					if ((i + 1) * packed_elements > independent_generators) {

						int rest = (i + 1) * packed_elements - independent_generators;
						rest = packed_elements - rest;


						for (int k = 0; k < packed_elements; k++) {
							if (k < rest)
								last_elements[k] = start_state[i * packed_elements + k];
							else
								last_elements[k] = 0;
						}
						state[i] = { set_reg<packet_type, uint64_t>(last_elements[7], last_elements[6], last_elements[5], last_elements[4], last_elements[3], last_elements[2], last_elements[1], last_elements[0]) };
					}
					else
						state[i] = { set_reg<packet_type, uint64_t>(start_state[i * packed_elements + 7], start_state[i * packed_elements + 6], start_state[i * packed_elements + 5], start_state[i * packed_elements + 4], start_state[i * packed_elements + 3], start_state[i * packed_elements + 2], start_state[i * packed_elements + 1], start_state[i * packed_elements + 0]) };
				}


#endif // __AVX512F__


			}
		}

		void init_packed_inc_array() {
			if (used_arch == InstructionSet::AVX2) {
#if __AVX2__
				uint64_t last_elements[packed_elements];
				for (int i = 0; i < min_required_state_registers; i++) {
					if ((i + 1) * packed_elements > independent_generators) {

						int rest = (i + 1) * packed_elements - independent_generators;
						rest = packed_elements - rest;

						for (int k = 0; k < packed_elements; k++) {
							if (k < rest)
								last_elements[k] = increment[i * packed_elements + k];
							else
								last_elements[k] = 0;
						}

						inc[i] = { set_reg<packet_type, uint64_t>(last_elements[3], last_elements[2], last_elements[1], last_elements[0]) };
					}
					else {
						inc[i] = { set_reg<packet_type, uint64_t>(increment[i * packed_elements + 3], increment[i * packed_elements + 2], increment[i * packed_elements + 1], increment[i * packed_elements + 0]) };
					}
				}
#endif
			}
			else if (used_arch == InstructionSet::AVX512)
			{
#ifdef SIMD_RNG_AVX512
				uint64_t last_elements[packed_elements];
				for (int i = 0; i < min_required_state_registers; i++) {
					if ((i + 1) * packed_elements > independent_generators) {

						int rest = (i + 1) * packed_elements - independent_generators;
						rest = packed_elements - rest;

						for (int k = 0; k < packed_elements; k++) {
							if (k < rest)
								last_elements[k] = increment[i * packed_elements + k];
							else
								last_elements[k] = 0;
						}
						inc[i] = { set_reg<packet_type, uint64_t>(last_elements[7], last_elements[6], last_elements[5], last_elements[4], last_elements[3], last_elements[2], last_elements[1], last_elements[0]) };
					}
					else
						inc[i] = { set_reg<packet_type, uint64_t>(increment[i * packed_elements + 7], increment[i * packed_elements + 6], increment[i * packed_elements + 5], increment[i * packed_elements + 4], increment[i * packed_elements + 3], increment[i * packed_elements + 2], increment[i * packed_elements + 1], increment[i * packed_elements + 0]) };
				}


#endif // __AVX512F__


			}
		}


		void init_packed_shuffle_idx() {
			if (used_arch == InstructionSet::AVX2) {
#if __AVX2__
				uint64_t last_elements[packed_elements];
				for (int i = 0; i < min_required_state_registers; i++) {
					if ((i + 1) * packed_elements > independent_generators) {

						int rest = (i + 1) * packed_elements - independent_generators;
						rest = packed_elements - rest;

						for (int k = 0; k < packed_elements; k++) {
							if (k < rest)
								last_elements[k] = i * packed_elements + k;
							else
								last_elements[k] = 0;
						}

						reg_idx[i] = set_reg<packet_type, uint64_t>(last_elements[3], last_elements[2], last_elements[1], last_elements[0]);
					}
					else {
						reg_idx[i] = set_reg<packet_type, uint64_t>(i * packed_elements + 3, i * packed_elements + 2, i * packed_elements + 1, i * packed_elements + 0);
					}
				}
#endif
			}
			else if (used_arch == InstructionSet::AVX512)
			{
#ifdef SIMD_RNG_AVX512
				uint64_t last_elements[packed_elements];
				for (int i = 0; i < min_required_state_registers; i++) {
					if ((i + 1) * packed_elements > independent_generators) {

						int rest = (i + 1) * packed_elements - independent_generators;
						rest = packed_elements - rest;

						for (int k = 0; k < packed_elements; k++) {
							if (k < rest)
								last_elements[k] = i * packed_elements + k;
							else
								last_elements[k] = 0;
						}
						reg_idx[i] = set_reg<packet_type, uint64_t>(last_elements[7], last_elements[6], last_elements[5], last_elements[4], last_elements[3], last_elements[2], last_elements[1], last_elements[0]);
					}
					else
						reg_idx[i] = set_reg<packet_type, uint64_t>(i * packed_elements + 7, i * packed_elements + 6, i * packed_elements + 5, i * packed_elements + 4, i * packed_elements + 3, i * packed_elements + 2, i * packed_elements + 1, i * packed_elements + 0);
				}


#endif // __AVX512F__


			}
		}


		void self_init() {
			base_generate0();

			Packed_result xdiff[min_required_state_registers];
			Packed_result table_init;

			for (int i = 0; i < min_required_state_registers; i++) {
				xdiff[i] = output_SIMD<used_arch, packet_type, result_type>(old_state[i]);
			}

			base_generate0();

			for (int i = 0; i < min_required_state_registers; i++) {
				xdiff[i] = xdiff[i] - output_SIMD<used_arch, packet_type, result_type>(old_state[i]);
			}

			for (int k = 0; k < table_k; k++) {

				base_generate0();

				for (int i = 0; i < min_required_state_registers; i++) {

					table_init = output_SIMD<used_arch, packet_type, result_type>(old_state[i]) ^ xdiff[i];

					if ((i == min_required_state_registers - 1) && does_spill_reg) {
						for (int j = 0; j < no_reg_spill_elements; j++) {

							if (j == 0) {
								table[i * packed_elements + j][k] = Extractor<extractor_const[0]>::template extract<std::uint32_t>(table_init.storage);
							}

							else if (j == 1) {
								table[i * packed_elements + j][k] = Extractor<extractor_const[1]>::template extract<std::uint32_t>(table_init.storage);
							}
							else if (j == 2) {
								table[i * packed_elements + j][k] = Extractor< extractor_const[2]>::template extract<std::uint32_t>(table_init.storage);
							}
							else if (j == 3) {
								table[i * packed_elements + j][k] = Extractor< extractor_const[3]>::template extract<std::uint32_t>(table_init.storage);
							}
#ifdef SIMD_RNG_AVX512
							else if (j == 4 && isAVX512) {
								table[i * packed_elements + j][k] = Extractor< extractor_const[4 % m]>::template extract<uint32_t>(table_init.storage);
							}
							else if (j == 5 && isAVX512) {
								table[i * packed_elements + j][k] = Extractor< extractor_const[5 % m]>::template extract<uint32_t>(table_init.storage);
							}
							else if (j == 6 && isAVX512) {
								table[i * packed_elements + j][k] = Extractor< extractor_const[6 % m]>::template extract<uint32_t>(table_init.storage);
							}
							else if (j == 7 && isAVX512) {
								table[i * packed_elements + j][k] = Extractor< extractor_const[7 % m]>::template extract<uint32_t>(table_init.storage);
							}
#endif
						}
					}

					else {
						for (int j = 0; j < packed_elements; j++) {
							if (j == 0) {
								table[i * packed_elements + j][k] = Extractor< extractor_const[0]>::template extract<std::uint32_t>(table_init.storage);
							}
							else if (j == 1) {
								table[i * packed_elements + j][k] = Extractor< extractor_const[1]>::template extract<std::uint32_t>(table_init.storage);
							}
							else if (j == 2) {
								table[i * packed_elements + j][k] = Extractor< extractor_const[2]>::template extract<std::uint32_t>(table_init.storage);
							}
							else if (j == 3) {
								table[i * packed_elements + j][k] = Extractor< extractor_const[3]>::template extract<std::uint32_t>(table_init.storage);
							}
#ifdef SIMD_RNG_AVX512
							else if (j == 4 && isAVX512) {
								table[i * packed_elements + j][k] = Extractor< extractor_const[4 % m]>::template extract<uint32_t>(table_init.storage);
							}
							else if (j == 5 && isAVX512) {
								table[i * packed_elements + j][k] = Extractor< extractor_const[5 % m]>::template extract<uint32_t>(table_init.storage);
							}
							else if (j == 6 && isAVX512) {
								table[i * packed_elements + j][k] = Extractor< extractor_const[6 % m]>::template extract<uint32_t>(table_init.storage);
							}
							else if (j == 7 && isAVX512) {
								table[i * packed_elements + j][k] = Extractor< extractor_const[7 % m]>::template extract<uint32_t>(table_init.storage);
							}
#endif
						}
					}
				}
			}
		}


		void init_shuffle() {

			for (int i = 0; i < min_required_state_registers; i++) {
				shuffle_mult[i] = mult;
				shuffle_inc[i] = inc[i];
				shuffle_idx[i] = { reg_idx[i] };
			}
			shuffle_mult[min_required_state_registers - 1] = fill_reg(shuffle_mult[min_required_state_registers - 1], shuffle_mult[0], unused_count);
			shuffle_inc[min_required_state_registers - 1] = fill_reg(shuffle_inc[min_required_state_registers - 1], shuffle_inc[0], unused_count);
			shuffle_idx[min_required_state_registers - 1] = fill_reg(shuffle_idx[min_required_state_registers - 1], shuffle_idx[0], unused_count);

			for (auto i = min_required_state_registers; i < reg_advances; i++) {
				shuffle_mult[i].storage = rotate_r_epi64<used_arch>(blendv_epi64<used_arch>(shuffle_mult[i - min_required_state_registers].storage, shuffle_mult[i - min_required_state_registers + 1].storage, unused_count), unused_count);
				shuffle_inc[i].storage = rotate_r_epi64<used_arch>(blendv_epi64<used_arch>(shuffle_inc[i - min_required_state_registers].storage, shuffle_inc[i - min_required_state_registers + 1].storage, unused_count), unused_count);
				shuffle_idx[i].storage = rotate_r_epi64<used_arch>(blendv_epi64<used_arch>(shuffle_idx[i - min_required_state_registers].storage, shuffle_idx[i - min_required_state_registers + 1].storage, unused_count), unused_count);
			}

			for (auto i = 0; i < reg_advances; i++) {
				storeInArray<used_arch>(&s_idx[i][0], shuffle_idx[i].storage);
			}
		}



		void bump(Packed_state(state_)[min_required_state_registers]) {

			for (int i = 0; i < min_required_state_registers; i++) {
				old_state[i] = state_[i];

				state[i] = mult * state_[i] + inc[i];
			}
		}



		Packed_state bump_s(Packed_state state_, Packed_state mult_, Packed_state inc_) {

			return mult_ * state_ + inc_;

		}
		void base_generate() {
			bump(state);
			//return state;
		}

		void base_generate0() {
			bump(state);
			//return old_state;
		}

		static bool external_step(std::uint32_t& randval, size_t i, std::uint32_t inc = lcg_constant32::increment, std::uint32_t mult = lcg_constant32::multiplier)
		{
			std::uint32_t tmp = rxs_m_xs_mix::unoutput1(randval);
			tmp = tmp * mult + inc + uint32_t(i * 2); //Must LCG be Increment must be odd
			std::uint32_t result = rxs_m_xs_mix::output1(tmp);
			randval = result;
			std::uint32_t zero = std::uint32_t(0U);

			return result == zero;
		}

		void advance_table(std::uint32_t(&table)[table_k]) {
			bool carry = false;
			for (size_t i = 0; i < table_k; ++i) {
				if (carry) {
					carry = external_step(table[i], i + 1);
				}
				bool carry2 = external_step(table[i], i + 1);
				carry = carry || carry2;
			}
		}

		inline Packed_result extract_table_val(__m256i current_state, std::int64_t(&idx)[packed_elements]) {
			const packet_type table_mask = mask::table_mask_packed4;
			packet_type index = _mm256_and_si256(current_state, table_mask);
			Packed_result tmp = { _mm_set_epi32(table[idx[3]][_mm256_extract_epi64(index, 3)], table[idx[2]][_mm256_extract_epi64(index, 2)], table[idx[1]][_mm256_extract_epi64(index, 1)], table[idx[0]][_mm256_extract_epi64(index, 0)]) };
			return tmp;

		}

#ifdef SIMD_RNG_AVX512

		inline Packed_result extract_table_val(__m512i current_state, int64_t(&idx)[packed_elements]) {

			__m512i index = _mm512_and_si512(current_state, mask::table_mask_packed8);
			__m256i index_l = _mm512_extracti32x8_epi32(index, 0);
			__m256i index_h = _mm512_extracti32x8_epi32(index, 1);
			return { _mm256_set_epi32(table[idx[7]][_mm256_extract_epi64(index_h, 3)], table[idx[6]][_mm256_extract_epi64(index_h, 2)], table[idx[5]][_mm256_extract_epi64(index_h, 1)], table[idx[4]][_mm256_extract_epi64(index_h, 0)],
							table[idx[3]][_mm256_extract_epi64(index_l, 3)], table[idx[2]][_mm256_extract_epi64(index_l, 2)], table[idx[1]][_mm256_extract_epi64(index_l, 1)], table[idx[0]][_mm256_extract_epi64(index_l, 0)]) };
		}
#endif


		inline Packed_result get_extended_values(Packed_state In, std::int64_t(&idx)[packed_elements])
		{
			auto tick = return_tick<used_arch, packet_type>(In.storage);

			if (test_if_advance<used_arch, packet_type>(tick)) {

				for (int j = 0; j < packed_elements; j++)
				{
					if (check_table_advance<used_arch, packet_type>(tick, j)) //tests if the lower bits in _state are all 0
					{
						advance_table(table[idx[j]]);
					}
				}
			}
			return extract_table_val(In.storage, idx);
		}

	};
};
