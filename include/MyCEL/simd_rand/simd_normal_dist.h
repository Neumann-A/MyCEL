#pragma once
#include <immintrin.h>
#include <type_traits>
#include <cstdlib>

#include "simd_lcg.h"
#include "definitions.h"

namespace array_simd_pcg {

	template<typename k, typename reg_type>
	inline auto normalize(reg_type In);

	template<>
	inline auto normalize<float>(__m128i In) {
		return _mm_add_ps(_mm_mul_ps(_mm_cvtepi32_ps(_mm_srlv_epi32(In, norm_const::norm_shift128)), norm_const::divisor128_24_ps),norm_const::divisor128_24_ps);
	}


	template<>
	inline auto normalize<float>(__m256i In) {
		return _mm256_add_ps(_mm256_mul_ps(_mm256_cvtepi32_ps(_mm256_srlv_epi32(In, norm_const::norm_shift256)), norm_const::divisor256_24_ps), norm_const::divisor256_24_ps);
	}

	template<>
	inline auto normalize<double>(__m128i In) {
		return _mm256_add_pd(_mm256_mul_pd(ucast<double>(In), norm_const::divisor256_64_pd),norm_const::divisor256_64_pd);
	}

#ifdef SIMD_RNG_AVX512
	template<>
	inline auto normalize<double>(__m256i In) {
		return _mm512_add_pd(_mm512_mul_pd(ucast<double>(In), norm_const::divisor512_64_pd), norm_const::divisor512_64_pd);
	}
#endif


	inline auto norm_dist(__m128 In, __m128 sigma) {
		return _mm_mul_ps(cdfnorminv(In), sigma);
	};

	inline auto norm_dist(__m256 In, __m256 sigma) {
		return _mm256_mul_ps(cdfnorminv(In), sigma);
	};

	inline auto norm_dist(__m256d In, __m256d sigma) {
		return _mm256_mul_pd(cdfnorminv(In), sigma);
	};

#ifdef SIMD_RNG_AVX512
	inline auto norm_dist(__m512d In, __m512d sigma) {
		return _mm512_mul_pd(cdfnorminv(In), sigma);
	};
#endif
// Old Version
//
//	template <unsigned int independent_generators = 32, std::uint16_t table_k = 1024, InstructionSet arch = InstructionSet::AVX2, typename outtype = float, std::uint16_t optimal_output = 32>
//	class norm_dist_rng :public packed_PCG<independent_generators, table_k, arch, optimal_output> {
//
//
//		using BaseRNG = packed_PCG<independent_generators, table_k, arch, optimal_output>;
//	public:
//		using BaseRNG::seed;
//		using BaseRNG::table_init;
//		using BaseRNG::set_inc;
//		using BaseRNG::set_multiplier;
//		using BaseRNG::get_state_advances;
//		using BaseRNG::get_Output_elems;
//		using BaseRNG::get_used_arch;
//	private:
//		constexpr static InstructionSet used_arch = BaseRNG::used_arch;
//
//
//		using f_AVX = std::conditional_t<used_arch == InstructionSet::AVX512, __m256, __m128>;
//#if __AVX512F__
//		using d_AVX = std::conditional_t<used_arch == InstructionSet::AVX512, __m512d, __m256d>;
//#else
//		using d_AVX = __m256d;
//#endif
//
//		using  output_type = std::conditional_t<std::is_same<outtype, float>::value, f_AVX, d_AVX>;
//
//		constexpr static int regcount = BaseRNG::get_Output_elems();
//		constexpr static int state_advances = BaseRNG::get_state_advances();
//
//		//output_type mu;
//
//		
//		output_type sigma;
//		output_type norm_res[regcount];
//		outtype tmp[state_advances * independent_generators];
//
//
//	public:
//		inline auto operator()() {
//			auto val = BaseRNG::operator()();
//			for (int j = 0; j < regcount; j++) {
//				norm_res[j] = norm_dist(normalize<outtype>(val[j].storage), sigma);
//				storeInArray<used_arch>(&tmp[j * BaseRNG::packed_elements], norm_res[j]);
//			}
//			return tmp;
//		}
//
//
//		norm_dist_rng(outtype StandardDeviation, uint64_t in_seed[independent_generators]) :BaseRNG(in_seed) {
//
//			sigma = set1_reg<output_type, outtype>(StandardDeviation);
//		}
//
//		norm_dist_rng(outtype StandardDeviation) :BaseRNG() {
//
//			sigma = set1_reg<output_type, outtype>(StandardDeviation);
//		}
//	};
//};


	template <class Engine, typename outtype=float>
	class norm_dist_rng{

	private:

		Engine *_E;
		outtype sigma;
		constexpr static InstructionSet used_arch=Engine::used_arch;
		constexpr static int independent_generators=Engine::num_generators;

		using f_AVX = std::conditional_t<used_arch == InstructionSet::AVX512, __m256, __m128>;
#if SIMD_RNG_AVX512
		using d_AVX = std::conditional_t<used_arch == InstructionSet::AVX512, __m512d, __m256d>;
#else
		using d_AVX = __m256d;
#endif

		using  output_type = std::conditional_t<std::is_same<outtype, float>::value, f_AVX, d_AVX>;

		constexpr static int regcount = Engine::get_Output_elems();
		constexpr static int calulated_results_per_generator = Engine::get_results_per_generator();

		//output_type mu;

		output_type sigma_v;
		output_type norm_res[regcount];
		alignas(16) outtype tmp[calulated_results_per_generator * independent_generators];


	public:
		inline auto operator()() {
			auto val = _E->operator()();
			for (int j = 0; j < regcount; j++) {
				norm_res[j] = norm_dist(normalize<outtype>(val[j].storage), sigma_v);
				storeInArray<used_arch>(&tmp[j * Engine::packed_elements], norm_res[j]);
			}
			return tmp;
		}

		template<typename prec=outtype>
		norm_dist_rng(Engine &E, outtype StandardDeviation) :_E(&E), sigma(StandardDeviation) {

			sigma_v = set1_reg<output_type, outtype>(StandardDeviation);
		}
		
		norm_dist_rng(Engine &E) :_E(&E), sigma(1) {

			sigma_v = set1_reg<output_type, outtype>(1);
		}
		
		norm_dist_rng() : sigma(1) {
			sigma_v = set1_reg<output_type, outtype>(1);
		}
	};
};
