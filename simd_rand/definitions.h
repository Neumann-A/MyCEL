#pragma once

#include <type_traits>
#include <immintrin.h>
#include <cstdint>
#include "constants.h"
#ifdef __clang__
	#include "../intrin/svml/avx_svml_intrin.h"
	#ifdef __AVX512F__
		#include "../intrin/svml/avx512_svml_intrin.h"
	#endif
#endif

namespace array_simd_pcg
{
	enum class InstructionSet { NONE, AVX, AVX2, AVX512 };


	template<InstructionSet set, typename _ = void>
	struct RegisterInfo
	{
		static_assert(std::is_same_v<set, set>, "Register Type is not defined for this arch!");
	};
#ifdef __AVX512F__
	template<typename T, typename _ = std::enable_if_t<std::disjunction_v<std::is_same<T, __m64>,
		std::is_same<T, __m128i>,
		std::is_same<T, __m256i>,
		std::is_same<T, __m512i>>>>
		struct BitSize
	{
		using type = T;
		constexpr static std::uint16_t bitsize() { return sizeof(T) * 8; };
	};
#endif
#ifndef __AVX512F__
	template<typename T, typename _ = std::enable_if_t<std::disjunction_v<std::is_same<T, __m64>,
		std::is_same<T, __m128i>,
		std::is_same<T, __m256i>>>>
		struct BitSize
	{
		using type = T;
		constexpr static std::uint16_t bitsize() { return sizeof(T) * 8; };
	};
#endif

		static_assert(BitSize<__m128i>::bitsize() == 128);
		static_assert(!(BitSize<__m128i>::bitsize() == 256));
		static_assert(BitSize<__m256i>::bitsize() == 256);

		template<typename T>
		struct PackedSize
		{
			template<typename U, typename _ = std::enable_if_t<std::is_integral_v<U>>>
			constexpr static auto packed_elements_size() {
				return T::bitsize() / (sizeof(U) * 8);
			}
		};

		template<>
		struct RegisterInfo<InstructionSet::NONE>
		{
			using type = std::int64_t;
			using ftype = float;
			using dtype = double;
			using half_type = std::int32_t;
			constexpr static std::uint16_t bitsize() { return sizeof(type) * 8; };
		};

		template<>
		struct RegisterInfo<InstructionSet::AVX> : BitSize<__m128i>, PackedSize<RegisterInfo<InstructionSet::AVX>>
		{
			using type = __m128i;
			using ftype = __m64;
			using dtype = __m128d;
			using lower_arch_register = RegisterInfo<InstructionSet::NONE>;
			using half_type = lower_arch_register::type;
		};

		template<>
		struct RegisterInfo<InstructionSet::AVX2> : BitSize<__m256i>, PackedSize<RegisterInfo<InstructionSet::AVX2>>
		{
			using type = __m256i;
			using ftype = __m128;
			using dtype = __m256d;
			using lower_arch_register = RegisterInfo<InstructionSet::AVX>;
			using half_type = lower_arch_register::type;
		};
#ifdef __AVX512F__
		template<>
		struct RegisterInfo<InstructionSet::AVX512> : BitSize<__m512i>, PackedSize<RegisterInfo<InstructionSet::AVX512>>
		{
			using type = __m512i;
			using ftype = __m256;
			using dtype = __m512d;
			using lower_arch_register = RegisterInfo<InstructionSet::AVX2>;
			using half_type = lower_arch_register::type;
		};
#endif
		template<InstructionSet set, typename reg_type, typename pack_type>
		struct PackedElements 
		{
			using value_t = PackedElements<set, reg_type, pack_type>;
			reg_type storage;
			using register_type = reg_type;
			using packed_type = pack_type;
			static constexpr auto instruction_set() { return set; }
			static constexpr auto packed_elements_size() { return PackedSize<reg_type>::template packed_elements_size<pack_type>(); }

			template<InstructionSet convertset>
			constexpr inline PackedElements<convertset, reg_type, pack_type> convertToArch() { return { this->storage }; };

};


#ifdef __AVX512F__
	static_assert(RegisterInfo<InstructionSet::AVX512>::bitsize() == 512 );
	static_assert(RegisterInfo<InstructionSet::AVX512>::packed_elements_size<std::uint64_t>() == 8);
	static_assert(RegisterInfo<InstructionSet::AVX512>::lower_arch_register::packed_elements_size<std::uint64_t>() == 4);
	//static_assert(PackedElements<InstructionSet::AVX512,__m512i,std::uint64_t>::packed_elements_size() == 8);
#endif

	template<unsigned int i>
	struct Extractor {

		template<typename out_type, typename reg_type>
		static inline out_type extract(reg_type reg) noexcept { static_assert(!std::is_same_v<reg_type, void>); };

#define EXTRACTOR_LOGIC(reg_width, reg_width_ret ,int_width) \
		template<> \
		static inline std::int ## int_width ## _t extract<std::int ## int_width ## _t, __m ## reg_width ## i > ( __m ## reg_width ## i reg ) noexcept \
		{ \
			/*static_assert(int_width * i < reg_width);*/	\
			return _mm ## reg_width_ret ## _extract_epi ## int_width (reg, i); \
		}; \
		template<> \
		static inline std::uint ## int_width ## _t extract<std::uint ## int_width ## _t, __m ## reg_width ## i > ( __m ## reg_width ## i reg ) noexcept \
		{ \
			/*static_assert(int_width * i < reg_width);*/	\
			return _mm ## reg_width_ret ## _extract_epi ## int_width (reg, i); \
		}

		EXTRACTOR_LOGIC(128, , 8);
		EXTRACTOR_LOGIC(128, , 16);
		EXTRACTOR_LOGIC(128, , 32);
		EXTRACTOR_LOGIC(128, , 64);
#ifdef __AVX2__
		EXTRACTOR_LOGIC(256, 256, 8);
		EXTRACTOR_LOGIC(256, 256, 16);
#endif
		EXTRACTOR_LOGIC(256, 256, 32);
		EXTRACTOR_LOGIC(256, 256, 64);

		template<>
		static inline __m128i extract< __m128i, __m256i>(__m256i reg) noexcept
		{
#if __AVX__ && !__AVX2__
#define _mm256_extracti128_si256 _mm256_extractf128_si256
#endif
			static_assert(128 * i < 256);
			return _mm256_extracti128_si256(reg, i);
#if __AVX__ && !__AVX2__
#undef _mm256_extracti128_si256
#endif
		};
#undef EXTRACTOR_LOGIC
	};
	

	struct NoSpareElements {
		const static bool spareElems = false;
	};
	struct SpareElements {
		const static bool spareElems = true;
	};


// extract low 32 bits
	template<typename reg_type, typename out_type, InstructionSet arch>
	inline PackedElements<arch, out_type, std::uint32_t> extract_low32(PackedElements<arch, reg_type, std::uint64_t> reg) noexcept;

#if __AVX2__
	template<>
	inline PackedElements<InstructionSet::AVX2, __m128i, std::uint32_t> extract_low32<__m256i, __m128i>(PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> reg) noexcept {

		return { _mm_set_epi32(_mm256_extract_epi32(reg.storage, 6), _mm256_extract_epi32(reg.storage, 4), _mm256_extract_epi32(reg.storage, 2), _mm256_extract_epi32(reg.storage, 0)) };
	}
#endif

#if __AVX512F__
	template<>
	inline PackedElements<InstructionSet::AVX512, __m256i, std::uint32_t> extract_low32<__m512i, __m256i>(PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> reg) noexcept {

		__m256i reg_L = _mm512_extracti32x8_epi32(reg.storage, 0);
		__m256i reg_H = _mm512_extracti32x8_epi32(reg.storage, 1);

		return { _mm256_set_epi32(_mm256_extract_epi32(reg_H, 6), _mm256_extract_epi32(reg_H, 4), _mm256_extract_epi32(reg_H, 2), _mm256_extract_epi32(reg_H, 0), _mm256_extract_epi32(reg_L, 6), _mm256_extract_epi32(reg_L, 4), _mm256_extract_epi32(reg_L, 2), _mm256_extract_epi32(reg_L, 0)) };
	}
#endif

	template<>
	inline PackedElements<InstructionSet::AVX, __m128i, std::uint32_t> extract_low32<__m256i, __m128i>(PackedElements<InstructionSet::AVX, __m256i, std::uint64_t> reg) noexcept {

		return { _mm_set_epi32(_mm256_extract_epi32(reg.storage, 6), _mm256_extract_epi32(reg.storage, 4), _mm256_extract_epi32(reg.storage, 2), _mm256_extract_epi32(reg.storage, 0)) };
	}


	template<typename reg_type,typename pack_type>
	inline reg_type set1_reg(pack_type val) noexcept;

	template<>
	inline __m128i set1_reg<__m128i, std::uint32_t>(std::uint32_t val) noexcept {
		return  _mm_set1_epi32(val);
	};
	template<>
	inline __m128i set1_reg<__m128i, int32_t>(std::int32_t val) noexcept {
		return  _mm_set1_epi32(val);
	};

	template<>
	inline __m128i set1_reg<__m128i, uint64_t>(std::uint64_t val) noexcept {
		return  _mm_set1_epi64x(val);
	};
	template<>
	inline __m128i set1_reg<__m128i, std::int64_t>(std::int64_t val) noexcept {
		return  _mm_set1_epi64x(val);
	};

	template<>
	inline __m256i set1_reg<__m256i, std::uint32_t>(std::uint32_t val) noexcept {
		return  _mm256_set1_epi32(val);
	};
	template<>
	inline __m256i set1_reg<__m256i, int32_t>(std::int32_t val) noexcept {
		return  _mm256_set1_epi32(val);
	};

	template<>
	inline __m256i set1_reg<__m256i, std::uint64_t>(std::uint64_t val) noexcept {
		return  _mm256_set1_epi64x(val);
	};
	template<>
	inline __m256i set1_reg<__m256i, std::int64_t>(std::int64_t val) noexcept {
		return  _mm256_set1_epi64x(val);
	};

	template<>
	inline __m128 set1_reg<__m128, float>(float val) noexcept {
		return  _mm_set1_ps(val);
	};
	template<>
	inline __m256 set1_reg<__m256, float>(float val) noexcept {
		return  _mm256_set1_ps(val);
	};

	template<>
	inline __m256d set1_reg<__m256d, double>(double val) noexcept {
		return  _mm256_set1_pd(val);
	};
	

#if __AVX512F__

	template<>
	inline __m512d set1_reg<__m512d, double>(double val) noexcept {
		return  _mm512_set1_pd(val);
	};



	template<>
	inline __m512i set1_reg<__m512i, std::uint32_t>(std::uint32_t val) noexcept {
		return  _mm512_set1_epi32(val);
	};
	template<>
	inline __m512i set1_reg<__m512i, int32_t>(std::int32_t val) noexcept {
		return  _mm512_set1_epi32(val);
	};

	template<>
	inline __m512i set1_reg<__m512i, std::uint64_t>(std::uint64_t val) noexcept {
		return  _mm512_set1_epi64(val);
	};
	template<>
	inline __m512i set1_reg<__m512i, std::int64_t>(std::int64_t val) noexcept {
		return  _mm512_set1_epi64(val);
	};
#endif

	template<typename reg_type, typename pack_type>
	inline reg_type set_reg(pack_type val1, pack_type val2, pack_type val3, pack_type val4) noexcept;

	template<>
	inline __m128i set_reg<__m128i, std::uint32_t>(std::uint32_t val1, std::uint32_t val2, std::uint32_t val3, std::uint32_t val4) noexcept {
		return _mm_set_epi32(val1, val2, val3, val4);
	};
	template<>
	inline __m128i set_reg<__m128i, int32_t>(int32_t val1, int32_t val2, int32_t val3, int32_t val4) noexcept {
		return _mm_set_epi32(val1, val2, val3, val4);
	};

	template<>
	inline __m256i set_reg<__m256i, std::uint64_t>(std::uint64_t val1, std::uint64_t val2, std::uint64_t val3, std::uint64_t val4) noexcept {
		return _mm256_set_epi64x(val1, val2, val3, val4);
	};
	template<>
	inline __m256i set_reg<__m256i, std::int64_t>(std::int64_t val1, std::int64_t val2, std::int64_t val3, std::int64_t val4) noexcept {
		return _mm256_set_epi64x(val1, val2, val3, val4);
	};

	template<typename reg_type, typename pack_type>
	inline reg_type set_reg(pack_type val1, pack_type val2, pack_type val3, pack_type val4, pack_type val5, pack_type val6, pack_type val7, pack_type val8) noexcept;
	template<>
	inline __m256i set_reg<__m256i, std::uint32_t>(std::uint32_t val1, std::uint32_t val2, std::uint32_t val3, std::uint32_t val4, std::uint32_t val5, std::uint32_t val6, std::uint32_t val7, std::uint32_t val8) noexcept {
		return _mm256_set_epi32(val1, val2, val3, val4, val5, val6, val7, val8);
	};
#if __AVX512F__
	template<>
	inline __m512i set_reg<__m512i, std::uint64_t>(std::uint64_t val1, std::uint64_t val2, std::uint64_t val3, std::uint64_t val4, std::uint64_t val5, std::uint64_t val6, uint64_t val7, uint64_t val8) noexcept {
		return _mm512_set_epi64(val1, val2, val3, val4, val5, val6, val7, val8);
	};
#endif

#ifdef __AVX512F__
	template<typename reg_type, typename pack_type>
	inline PackedElements<InstructionSet::AVX512, reg_type, pack_type> operator>>(PackedElements<InstructionSet::AVX512, reg_type, pack_type> Input, PackedElements<InstructionSet::AVX512, reg_type, pack_type> Shift);

	template<>
	inline PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> operator>>(PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> Input, PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> Shift) {
		const auto RegIn = Input.storage;
		const auto shift = Shift.storage;
		return { _mm512_srlv_epi64(RegIn, shift) };
	};
	template<>
	inline PackedElements<InstructionSet::AVX512, __m512i, std::uint32_t> operator>>(PackedElements<InstructionSet::AVX512, __m512i, std::uint32_t> Input, PackedElements<InstructionSet::AVX512, __m512i, std::uint32_t> Shift) {
		const auto RegIn = Input.storage;
		const auto shift = Shift.storage;
		return { _mm512_srlv_epi32(RegIn, shift) };
	};


	template<typename reg_type, typename pack_type>
	inline PackedElements<InstructionSet::AVX512, reg_type, pack_type> operator<<(PackedElements<InstructionSet::AVX512, reg_type, pack_type> Input, PackedElements<InstructionSet::AVX512, reg_type, pack_type> Shift);

	template<>
	inline PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> operator<<(PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> Input, PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> Shift) {
		const auto RegIn = Input.storage;
		const auto shift = Shift.storage;
		return { _mm512_sllv_epi64(RegIn, shift) };
	};
	template<>
	inline PackedElements<InstructionSet::AVX512, __m512i, std::uint32_t> operator<<(PackedElements<InstructionSet::AVX512, __m512i, std::uint32_t> Input, PackedElements<InstructionSet::AVX512, __m512i, std::uint32_t> Shift) {
		const auto RegIn = Input.storage;
		const auto shift = Shift.storage;
		return { _mm512_sllv_epi32(RegIn, shift) };
	};

	template<typename reg_type, typename pack_type>
	inline PackedElements<InstructionSet::AVX512, reg_type, pack_type> packed_rotate_right(PackedElements<InstructionSet::AVX512, reg_type, pack_type> Input, PackedElements<InstructionSet::AVX512, reg_type, pack_type> rot);

	template<>
	inline PackedElements<InstructionSet::AVX512, __m256i, std::uint32_t> packed_rotate_right<__m256i, std::uint32_t>(PackedElements<InstructionSet::AVX512, __m256i, std::uint32_t> Input, PackedElements<InstructionSet::AVX512, __m256i, std::uint32_t> rot) {
		const auto RegIn = Input.storage;
		const auto shift = rot.storage;
		return { _mm256_rorv_epi32(RegIn, shift) };
	};
	template<>
	inline PackedElements<InstructionSet::AVX512, __m128i, std::uint32_t> packed_rotate_right<__m128i, std::uint32_t>(PackedElements<InstructionSet::AVX512, __m128i, std::uint32_t> Input, PackedElements<InstructionSet::AVX512, __m128i, std::uint32_t> rot) {
		const auto RegIn = Input.storage;
		const auto shift = rot.storage;
		return { _mm_rorv_epi32(RegIn, shift) };
	};

	inline PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> operator*(PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> In1, PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> In2)
	{
		const auto RegIn1 = In1.storage;
		const auto RegIn2 = In2.storage;
		
		return { _mm512_mullo_epi64(RegIn1, RegIn2) };
	};

	inline PackedElements<InstructionSet::AVX512, __m256i, std::uint64_t> operator*(PackedElements<InstructionSet::AVX512, __m256i, std::uint64_t> In1, PackedElements<InstructionSet::AVX512, __m256i, std::uint64_t> In2)
	{
		const auto RegIn1 = In1.storage;
		const auto RegIn2 = In2.storage;

		return { _mm256_mullo_epi64(RegIn1, RegIn2) };
	};

#endif

#ifdef __AVX2__
	template<typename reg_type, typename pack_type>
	inline PackedElements<InstructionSet::AVX2, reg_type, pack_type> operator>>(PackedElements<InstructionSet::AVX2, reg_type, pack_type> Input, PackedElements<InstructionSet::AVX2, reg_type, pack_type> Shift);

	template<>
	inline PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> operator>>(PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> Input, PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> Shift) {
		const auto RegIn = Input.storage;
		const auto shift = Shift.storage;
		return { _mm256_srlv_epi64(RegIn, shift) };
	};
	template<>
	inline PackedElements<InstructionSet::AVX2, __m128i, std::uint64_t> operator>>(PackedElements<InstructionSet::AVX2, __m128i, std::uint64_t> Input, PackedElements<InstructionSet::AVX2, __m128i, std::uint64_t> Shift) {
		const auto RegIn = Input.storage;
		const auto shift = Shift.storage;
		return { _mm_srlv_epi64(RegIn, shift) };
	};

	template<typename reg_type, typename pack_type>
	inline PackedElements<InstructionSet::AVX2, reg_type, pack_type> operator<<(PackedElements<InstructionSet::AVX2, reg_type, pack_type> Input, PackedElements<InstructionSet::AVX2, reg_type, pack_type> Shift);

	template<>
	inline PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> operator<<(PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> Input, PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> Shift) {
		const auto RegIn = Input.storage;
		const auto shift = Shift.storage;
		return { _mm256_sllv_epi64(RegIn, shift) };
	};
	template<>
	inline PackedElements<InstructionSet::AVX2, __m128i, std::uint64_t> operator<<(PackedElements<InstructionSet::AVX2, __m128i, std::uint64_t> Input, PackedElements<InstructionSet::AVX2, __m128i, std::uint64_t> Shift) {
		const auto RegIn = Input.storage;
		const auto shift = Shift.storage;
		return { _mm_sllv_epi64(RegIn, shift) };
	};

	template<typename reg_type, typename pack_type>
	inline PackedElements<InstructionSet::AVX2, reg_type, pack_type> packed_rotate_right(PackedElements<InstructionSet::AVX2, reg_type, pack_type> Input, PackedElements<InstructionSet::AVX2, reg_type, pack_type> rot);

	template<>
	inline PackedElements<InstructionSet::AVX2, __m128i, std::uint32_t> packed_rotate_right<__m128i, std::uint32_t>(PackedElements<InstructionSet::AVX2, __m128i, std::uint32_t> Input, PackedElements<InstructionSet::AVX2, __m128i, std::uint32_t> rot) {
		const auto RegIn = Input.storage;
		const auto shift = rot.storage;
			  auto rotl = _mm_set1_epi32(32);
		rotl = _mm_sub_epi32(rotl, shift);
		return { _mm_or_si128(_mm_srlv_epi32(RegIn, shift), _mm_sllv_epi32(RegIn, rotl))};
	};


	inline PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> operator*(PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> In1, PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> In2)
	{
		const auto RegIn1 = In1.storage;
		const auto RegIn2 = In2.storage;

		/*std::cout << uint64_t(_mm256_extract_epi64(RegIn1, 0)) << std::endl;
		std::cout << uint64_t(_mm256_extract_epi64(RegIn2, 0))<<"\n\n\n\n"<< std::endl;*/

		const auto lowmask_packed4 = _mm256_set1_epi64x(0x00000000ffffffffull);

		//The shifts and masks generate a bit faster code than using _mm256_mullo_epi32 and packing the hl and lh calc into one instruction.

		const auto mh = _mm256_srli_epi64(RegIn1, 32);				// Move multiplier high into lower 32 bits
		const auto ml = _mm256_and_si256(RegIn1, lowmask_packed4);   // get low part of multiplier
		const auto xl = _mm256_and_si256(RegIn2, lowmask_packed4);			// get low part of x

		const auto xh = _mm256_srli_epi64(RegIn2, 32); // move x high part to low
		const auto hl = _mm256_slli_epi64(_mm256_mul_epu32(xh, ml), 32); // Multiply high x with * low mult and move the result high 
		const auto lh = _mm256_slli_epi64(_mm256_mul_epu32(xl, mh), 32); // Multiply low x with * high mult and move the result high 

		const auto highres = _mm256_add_epi64(hl, lh);
		const auto lowres = _mm256_mul_epu32(xl, ml);


		return { _mm256_add_epi64(highres, lowres) };
	};

	inline PackedElements<InstructionSet::AVX2, __m128i, std::uint64_t> operator*(PackedElements<InstructionSet::AVX2, __m128i, std::uint64_t> In1, PackedElements<InstructionSet::AVX2, __m128i, std::uint64_t> In2)
	{
		const auto RegIn1 = In1.storage;
		const auto RegIn2 = In2.storage;
		const auto lowmask_packed4 = _mm_set1_epi64x(0x00000000ffffffffull);

		//The shifts and masks generate a bit faster code than using _mm256_mullo_epi32 and packing the hl and lh calc into one instruction.

		const auto mh = _mm_srli_epi64(RegIn1, 32);				// Move multiplier high into lower 32 bits
		const auto ml = _mm_and_si128(RegIn1, lowmask_packed4);   // get low part of multiplier
		const auto xl = _mm_and_si128(RegIn2, lowmask_packed4);			// get low part of x

		const auto xh = _mm_srli_epi64(RegIn2, 32); // move x high part to low
		const auto hl = _mm_slli_epi64(_mm_mul_epu32(xh, ml), 32); // Multiply high x with * low mult and move the result high 
		const auto lh = _mm_slli_epi64(_mm_mul_epu32(xl, mh), 32); // Multiply low x with * high mult and move the result high 

		const auto highres = _mm_add_epi64(hl, lh);
		const auto lowres = _mm_mul_epu32(xl, ml);


		return { _mm_add_epi64(highres, lowres) };
	};

	template<typename reg_type,typename pack_type>
	inline PackedElements<InstructionSet::AVX2, reg_type, pack_type> operator^(PackedElements<InstructionSet::AVX2, reg_type, pack_type> In1, PackedElements<InstructionSet::AVX2, reg_type, pack_type> In2);
	
	template<>
	inline PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> operator^(PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> In1, PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> In2) {
		auto A = In1.storage;
		auto B = In2.storage;
		return { _mm256_xor_si256(A,B) };
	};

	template<>
	inline PackedElements<InstructionSet::AVX2, __m256i, std::uint32_t> operator^(PackedElements<InstructionSet::AVX2, __m256i, std::uint32_t> In1, PackedElements<InstructionSet::AVX2, __m256i, std::uint32_t> In2) {
		auto A = In1.storage;
		auto B = In2.storage;
		return { _mm256_xor_si256(A,B) };
	};

	template<>
	inline PackedElements<InstructionSet::AVX2, __m128i, std::uint32_t> operator^(PackedElements<InstructionSet::AVX2, __m128i, std::uint32_t> In1, PackedElements<InstructionSet::AVX2, __m128i, std::uint32_t> In2) {
		auto A = In1.storage;
		auto B = In2.storage;
		return { _mm_xor_si128(A,B) };
	};

	template<typename reg_type, typename pack_type>
	inline PackedElements<InstructionSet::AVX512, reg_type, pack_type> operator^(PackedElements<InstructionSet::AVX512, reg_type, pack_type> In1, PackedElements<InstructionSet::AVX512, reg_type, pack_type> In2);

	template<>
	inline PackedElements<InstructionSet::AVX512, __m256i, std::uint32_t> operator^(PackedElements<InstructionSet::AVX512, __m256i, std::uint32_t> In1, PackedElements<InstructionSet::AVX512, __m256i, std::uint32_t> In2) {
		auto A = In1.storage;
		auto B = In2.storage;
		return { _mm256_xor_si256(A,B) };
	};

#ifdef __AVX512F__
	template<>
	inline PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> operator^(PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> In1, PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> In2) {
		auto A = In1.storage;
		auto B = In2.storage;
		return { _mm512_xor_si512(A,B) };
	};
#endif // __AVX512F__
	template<typename reg_type, typename pack_type>
	inline PackedElements<InstructionSet::AVX2, reg_type, pack_type> operator+(PackedElements<InstructionSet::AVX2, reg_type, pack_type> In1, PackedElements<InstructionSet::AVX2, reg_type, pack_type> In2);

	template<>
	inline PackedElements<InstructionSet::AVX2, __m256i, std::uint32_t> operator+(PackedElements<InstructionSet::AVX2, __m256i, std::uint32_t> In1, PackedElements<InstructionSet::AVX2, __m256i, std::uint32_t> In2) {
		return { _mm256_add_epi32(In1.storage,In2.storage) };
	};

	template<>
	inline PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> operator+(PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> In1, PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> In2) {
		return { _mm256_add_epi64(In1.storage,In2.storage) };
	};


	template<typename reg_type, typename pack_type>
	inline PackedElements<InstructionSet::AVX512, reg_type, pack_type> operator-(PackedElements<InstructionSet::AVX512, reg_type, pack_type> In1, PackedElements<InstructionSet::AVX512, reg_type, pack_type> In2);

	template<>
	inline PackedElements<InstructionSet::AVX512, __m256i, std::uint32_t> operator-(PackedElements<InstructionSet::AVX512, __m256i, std::uint32_t> In1, PackedElements<InstructionSet::AVX512, __m256i, std::uint32_t> In2) {
		return { _mm256_sub_epi32(In1.storage,In2.storage) };
	};


	template<typename reg_type, typename pack_type>
	inline PackedElements<InstructionSet::AVX2, reg_type, pack_type> operator-(PackedElements<InstructionSet::AVX2, reg_type, pack_type> In1, PackedElements<InstructionSet::AVX2, reg_type, pack_type> In2);

	template<>
	inline PackedElements<InstructionSet::AVX2, __m128i, std::uint32_t> operator-(PackedElements<InstructionSet::AVX2, __m128i, std::uint32_t> In1, PackedElements<InstructionSet::AVX2, __m128i, std::uint32_t> In2) {
		return { _mm_sub_epi32(In1.storage,In2.storage) };
	};

	template<typename reg_type, typename pack_type>
	inline PackedElements<InstructionSet::AVX2, reg_type, pack_type> operator&(PackedElements<InstructionSet::AVX2, reg_type, pack_type> In1, PackedElements<InstructionSet::AVX2, reg_type, pack_type> In2);

	template<>
	inline PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> operator&(PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> In1, PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> In2) {
		return { _mm256_and_si256(In1.storage,In2.storage) };
	};

	template<>
	inline PackedElements<InstructionSet::AVX2, __m256i, std::uint32_t> operator&(PackedElements<InstructionSet::AVX2, __m256i, std::uint32_t> In1, PackedElements<InstructionSet::AVX2, __m256i, std::uint32_t> In2) {
		return { _mm256_and_si256(In1.storage,In2.storage) };
	};
	
#endif

#ifdef __AVX512F__
	template<typename reg_type, typename pack_type>
	inline PackedElements<InstructionSet::AVX512, reg_type, pack_type> operator+(PackedElements<InstructionSet::AVX512, reg_type, pack_type> In1, PackedElements<InstructionSet::AVX512, reg_type, pack_type> In2);

	template<>
	inline PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> operator+(PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> In1, PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> In2) {
		return { _mm512_add_epi64(In1.storage,In2.storage) };
	};

	template<typename reg_type, typename pack_type>
	inline PackedElements<InstructionSet::AVX512, reg_type, pack_type> operator&(PackedElements<InstructionSet::AVX512, reg_type, pack_type> In1, PackedElements<InstructionSet::AVX512, reg_type, pack_type> In2);

	template<>
	inline PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> operator&(PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> In1, PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> In2) {
		return { _mm512_and_si512(In1.storage,In2.storage) };
	};

	template<>
	inline PackedElements<InstructionSet::AVX512, __m512i, std::uint32_t> operator&(PackedElements<InstructionSet::AVX512, __m512i, std::uint32_t> In1, PackedElements<InstructionSet::AVX512, __m512i, std::uint32_t> In2) {
		return { _mm512_and_si512(In1.storage,In2.storage) };
	};
#endif



	template<InstructionSet arch, typename reg_type, typename pack_type>
	inline void mask_store(pack_type* mem_addr, int elem, reg_type a);

#ifdef __AVX512F__
		template<>
		inline void mask_store<InstructionSet::AVX512>(double* mem_addr, int elem, __m512d a) {
			_mm512_mask_storeu_pd(mem_addr, (0b00000001<<elem)|1, a);
		}
		template<>
		inline void mask_store<InstructionSet::AVX512>(int* mem_addr, int elem, __m256i a) {
			_mm256_maskstore_epi32(mem_addr, mask::select_element8[elem], a);
		}
#endif

		template<>
		inline void mask_store<InstructionSet::AVX2>(double* mem_addr, int elem, __m256d a) {
			_mm256_maskstore_pd(mem_addr, mask::select_element4_pd[elem], a);
		}

		template<>
		inline void mask_store<InstructionSet::AVX2>(int* mem_addr, int elem, __m128i a) {
			_mm_maskstore_epi32(mem_addr, mask::select_element4[elem], a);
		}


		template<InstructionSet arch,typename reg_type, typename packtype>
		inline void storeInArray(packtype* mem_addr, reg_type a);

#if __AVX2__
		template<>
		inline void storeInArray<InstructionSet::AVX2, __m256i>(std::int64_t* mem_addr, __m256i a) {
			_mm256_maskstore_epi64(mem_addr, _mm256_set1_epi64x((unsigned long long)(-1)), a);
		}

		template<>
		inline void storeInArray<InstructionSet::AVX2, __m128>(float* mem_addr, __m128 a) {
			_mm_store_ps(mem_addr, a);
		}

		template<>
		inline void storeInArray<InstructionSet::AVX2, __m256d>(double* mem_addr, __m256d a) {
			_mm256_store_pd(mem_addr, a);
		}

		template<>
		inline void storeInArray<InstructionSet::AVX512, __m256>(float* mem_addr, __m256 a) {
			_mm256_store_ps(mem_addr, a);
		}
#endif

#if __AVX512F__
		template<>
		inline void storeInArray<InstructionSet::AVX512, __m512i>(std::int64_t* mem_addr, __m512i a) {
			_mm512_mask_store_epi64(mem_addr, __mmask8(0b11111111), a);
		}

		template<>
		inline void storeInArray<InstructionSet::AVX512, __m512d>(double* mem_addr, __m512d a) {
			_mm512_mask_store_pd(mem_addr, __mmask8(0b11111111), a);
		}
#endif




	template<typename pack_type, typename reg_type>
	inline auto  ucast(reg_type In);

	template<>
	inline auto ucast<float>(__m128i In) {
		return _mm_add_ps(_mm_cvtepi32_ps(In), norm_const::min128_32_ps);
	}

	//template<>
	//inline auto ucast<float>(__m256i In) {
	//	return _mm256_add_ps(_mm256_cvtepi32_ps(In), norm_const::min256_32_ps);
	//}

	/*template<>
	inline auto ucast<float>(__m128i In) {
		return _mm256_cvtpd_ps(_mm256_add_pd(_mm256_cvtepi32_pd(In), norm_const::min256_32_pd));
	}*/

	template<>
	inline auto ucast<double>(__m128i In) {
		return _mm256_add_pd(_mm256_cvtepi32_pd(In), norm_const::min256_32_pd);
	}

#ifdef __AVX512F__

	template<>
	inline auto ucast<float>(__m256i In) {
		return _mm512_cvtpd_ps(_mm512_cvtepu32_pd(In));
	}

	template<>
	inline auto ucast<double>(__m256i In) {
		return _mm512_cvtepu32_pd(In);
	}

	

#endif // __AVX5112F__

	inline auto cdfnorminv(__m128 In) {
		return _mm_cdfnorminv_ps(In);
	}

	inline auto cdfnorminv(__m256 In) {
		return _mm256_cdfnorminv_ps(In);
	}

	inline auto cdfnorminv(__m256d In) {
		return _mm256_cdfnorminv_pd(In);
	}
#ifdef __AVX512F__
	inline auto cdfnorminv(__m512d In) {
		return _mm512_cdfnorminv_pd(In);
	}
#endif // __AVX5112F__


#ifdef __AVX2__
	template<InstructionSet arch,typename reg_type>
	inline reg_type return_tick(reg_type state);

	template<>
	inline __m256i return_tick<InstructionSet::AVX2, __m256i>(__m256i state) {
		return  _mm256_and_si256(mask::t_mask_packed4, state);
	}

	template<InstructionSet arch, typename reg_type>
	inline bool test_if_advance(reg_type state);

	template<>
	inline bool test_if_advance<InstructionSet::AVX2, __m256i>(__m256i tick) {
		return (_mm256_testz_si256(_mm256_cmpeq_epi32(tick, _mm256_set1_epi64x(0)), mask::advcase4) == 0);
	}

	template<InstructionSet arch, typename reg_type>
	inline bool check_table_advance(reg_type state, int idx);

	template<>
	inline bool check_table_advance<InstructionSet::AVX2, __m256i>(__m256i tick, int idx) {
		return (_mm256_testz_si256(tick, mask::ifmask4[idx]));
	}



#endif
#ifdef __AVX512F__
	template<>
	inline __m512i return_tick<InstructionSet::AVX512, __m512i>(__m512i state) {
		return _mm512_and_epi64(mask::t_mask_packed8, state);
	}

	template<InstructionSet arch, typename reg_type>
	inline bool test_if_advance(reg_type state);

	template<>
	inline bool test_if_advance<InstructionSet::AVX512, __m512i>(__m512i tick) {
		return _mm512_testn_epi64_mask(tick, mask::advcase8) != 0b00000000;
	}

	template<InstructionSet arch, typename reg_type>
	inline bool check_table_advance(reg_type state, int idx);

	template<>
	inline bool check_table_advance<InstructionSet::AVX512, __m512i>(__m512i tick, int idx) {
		return _mm512_testn_epi64_mask(tick, mask::ifmask8[idx]) == 0b11111111;
	}

#endif
	   	 
	template<InstructionSet arch, typename regtype, typename outtype>
	inline PackedElements<arch, regtype, outtype> fill_reg(PackedElements<arch, regtype, outtype> reg2fill, PackedElements<arch, regtype, outtype> fillreg, int empty_segs) {
	}

	template<InstructionSet arch, typename reg_type>
	reg_type blendv_epi64(reg_type a, reg_type b, int unused) {
	}

	template<InstructionSet arch, typename reg_type>
	reg_type rotate_r_epi64(reg_type a, int i) {
	};

	template<InstructionSet arch, typename reg_type>
	reg_type rotate_l_epi64(reg_type a, int i) {
	};


#ifdef __AVX2__
	template<>
	inline PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> fill_reg<InstructionSet::AVX2, __m256i, std::uint64_t>(PackedElements<InstructionSet::AVX2, __m256i, std::uint64_t> reg2fill, PackedElements<InstructionSet::AVX2, __m256i, uint64_t> fillreg, int empty_segs) {
		int shift = 4 - empty_segs;
		return { _mm256_castpd_si256(_mm256_blendv_pd(_mm256_castsi256_pd(reg2fill.storage), _mm256_castsi256_pd(_mm256_permutevar8x32_epi32(fillreg.storage, rot::rot4l[shift])), _mm256_castsi256_pd(rot::blend_fill4[empty_segs]))) };
	}
	
	template<>
	__m256i blendv_epi64<InstructionSet::AVX2,__m256i>(__m256i a, __m256i b, int unused) {

		return _mm256_castpd_si256(_mm256_blendv_pd(_mm256_castsi256_pd(a), _mm256_castsi256_pd(b), _mm256_castsi256_pd(rot::blend_select4[unused]) ));
	}

	
	template<>
	__m256i rotate_r_epi64<InstructionSet::AVX2, __m256i>(__m256i a, int i) {
		return _mm256_permutevar8x32_epi32(a, rot::rot4r[i]);
	};

	template<>
	__m256i rotate_l_epi64<InstructionSet::AVX2, __m256i>(__m256i a, int i) {
		return _mm256_permutevar8x32_epi32(a, rot::rot4l[i]);
	};


#endif
	
#if __AVX512F__
	template<>
	__m512i blendv_epi64<InstructionSet::AVX512, __m512i>(__m512i a, __m512i b, int unused) {

		return _mm512_mask_blend_epi64(rot::blend_select8[unused], a, b);
	}

	template<>
	__m512i rotate_r_epi64<InstructionSet::AVX512, __m512i>(__m512i a, int i) {
		return _mm512_permutexvar_epi64(rot::rot8r[i],a);
	};

	template<>
	__m512i rotate_l_epi64<InstructionSet::AVX512, __m512i>(__m512i a, int i) {
		return _mm512_permutexvar_epi64(rot::rot8l[i],a);
	};

	template<>
	inline PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> fill_reg<InstructionSet::AVX512, __m512i, std::uint64_t>(PackedElements<InstructionSet::AVX512, __m512i, std::uint64_t> reg2fill, PackedElements<InstructionSet::AVX512, __m512i, uint64_t> fillreg, int empty_segs) {
		return { _mm512_mask_expand_epi64(reg2fill.storage,rot::blend_fill8[empty_segs],fillreg.storage) };
	}

#endif

};
