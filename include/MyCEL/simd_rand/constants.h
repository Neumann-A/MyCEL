#pragma once
#include <immintrin.h>
#include <cstdint>

namespace mcg_constant_32 {
	const __m128i multiplier128		= _mm_set1_epi32(277803737U);
	const __m128i unmultiplier128		= _mm_set1_epi32(2897767785U);
	alignas(16) constexpr const std::uint32_t multiplier		= 277803737U;
	alignas(16) constexpr const std::uint32_t unmultiplier		= 2897767785U;
}
namespace lcg_constant64 {
#if __AVX512F__
		__m512i increment512	= _mm512_set1_epi64(1442695040888963407ULL);
		__m512i multiplier512	= _mm512_set1_epi64(6364136223846793005ULL);
#endif
		const __m256i increment256	= _mm256_set1_epi64x(1442695040888963407ULL);
		const __m256i multiplier256	= _mm256_set1_epi64x(6364136223846793005ULL);
		alignas(16) constexpr const std::uint64_t increment		= 1442695040888963407ULL;
		alignas(16) constexpr const std::uint64_t multiplier	= 6364136223846793005ULL;
	 
}
namespace lcg_constant32 {
	//__m256i increment256	= _mm256_set1_epi32(2891336453U);
	//__m256i multiplier256	= _mm256_set1_epi32(747796405U);
	const __m128i increment128	= _mm_set1_epi32(2891336453U);
	const __m128i multiplier128	= _mm_set1_epi32(747796405U);
	alignas(16) constexpr const std::uint32_t increment	= 2891336453U;
	alignas(16) constexpr const std::uint32_t multiplier	= 747796405U;
}

namespace mask {
	alignas(16) constexpr const std::uint64_t table_mask_const = ((1 << 10) - 1);
    alignas(16) constexpr const std::uint64_t t_mask = (1 << 16) - 1;
#if __AVX512F__
	const __m512i t_mask_packed8 = _mm512_set1_epi64(t_mask);
	const __m512i table_mask_packed8 = _mm512_set1_epi64(table_mask_const);
	const __m512i lowmask_packed5 = _mm512_set1_epi64(0x00000000ffffffffull);
#endif
    const __m256i t_mask_packed4 = _mm256_set1_epi64x(t_mask);
	const __m256i table_mask_packed4 = _mm256_set1_epi64x(table_mask_const);
	const __m256i lowmask_packed4 = _mm256_set1_epi64x(0x00000000ffffffffull);

#if __AVX512F__
	const __m512i ifmask8[8] = { _mm512_set_epi32(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,(unsigned)(-1u)),_mm512_set_epi32(0,0,0,0,0,0,0,0,0,0,0,0,0,(unsigned)(-1u),0,0),_mm512_set_epi32(0,0,0,0,0,0,0,0,0,0,0,(unsigned)(-1u),0,0,0,0),_mm512_set_epi32(0,0,0,0,0,0,0,0,0,(unsigned)(-1u),0,0,0,0,0,0),
									_mm512_set_epi32(0,0,0,0,0,0,0,(unsigned)(-1u),0,0,0,0,0,0,0,0),_mm512_set_epi32(0,0,0,0,0,(unsigned)(-1u),0,0,0,0,0,0,0,0,0,0),_mm512_set_epi32(0,0,0,(unsigned)(-1u),0,0,0,0,0,0,0,0,0,0,0,0),_mm512_set_epi32(0,(unsigned)(-1u),0,0,0,0,0,0,0,0,0,0,0,0,0,0) };
	const __m512i advcase8 = _mm512_set_epi32(0, (unsigned)(-1u), 0, (unsigned)(-1u), 0, (unsigned)(-1u), 0, (unsigned)(-1u), 0, (unsigned)(-1u), 0, (unsigned)(-1u), 0, (unsigned)(-1u), 0, (unsigned)(-1u));
#endif
	const __m256i ifmask4[4] = { _mm256_set_epi32(0,0,0,0,0,0,0,(unsigned)(-1u)),_mm256_set_epi32(0,0,0,0,0,(unsigned)(-1u),0,0),_mm256_set_epi32(0,0,0,(unsigned)(-1u),0,0,0,0),_mm256_set_epi32(0,(unsigned)(-1u),0,0,0,0,0,0) };
	const __m256i advcase4 = _mm256_set_epi32(0, (unsigned)(-1u), 0, (unsigned)(-1u), 0, (unsigned)(-1u), 0, (unsigned)(-1u));


	__m256i select_element8[8]= { _mm256_set_epi32((unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u)),_mm256_set_epi32(0,0,0,0,0,0,0,(unsigned)(-1u)),_mm256_set_epi32(0,0,0,0,0,0,(unsigned)(-1u),(unsigned)(-1u)),_mm256_set_epi32(0,0,0,0,0,(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u)),_mm256_set_epi32(0,0,0,0,(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u)),_mm256_set_epi32(0,0,0,(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u)),
									_mm256_set_epi32(0,0,(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u)),_mm256_set_epi32(0,(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u)) };
	
	__m128i select_element4[4] = { _mm_set_epi32((unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u)),_mm_set_epi32(0,0,0,(unsigned)(-1u)),_mm_set_epi32(0,0,(unsigned)(-1u),(unsigned)(-1u)),_mm_set_epi32(0,(unsigned)(-1u),(unsigned)(-1u),(unsigned)(-1u)) };

	__m256i select_element4_pd[4] = { _mm256_set_epi64x((unsigned long long)(-1ull),(unsigned long long)(-1ull),(unsigned long long)(-1ull),(unsigned long long)(-1ull)),_mm256_set_epi64x(0,0,0,(unsigned long long)(-1ull)),_mm256_set_epi64x(0,0,(unsigned long long)(-1ull),(unsigned long long)(-1ull)),_mm256_set_epi64x(0,(unsigned long long)(-1ull),(unsigned long long)(-1ull),(unsigned long long)(-1ull)) };
	
	const int perm_rot4[4] = { 0b11100100,0b10010011,0b01001110,0b00111001 };
}

namespace rot {
	__m256i rot4l[4] = { _mm256_set_epi32(7,6,5,4,3,2,1,0),_mm256_set_epi32(5,4,3,2,1,0,7,6),_mm256_set_epi32(3,2,1,0,7,6,5,4),
		_mm256_set_epi32(1,0,7,6,5,4,3,2) };

	__m256i rot4r[4] = { _mm256_set_epi32(7,6,5,4,3,2,1,0),_mm256_set_epi32(1,0,7,6,5,4,3,2),_mm256_set_epi32(3,2,1,0,7,6,5,4),
		_mm256_set_epi32(5,4,3,2,1,0,7,6) };

	__m256i blend_fill4[4] = { _mm256_set1_epi64x(0), _mm256_set_epi64x((unsigned long long)(-1),0,0,0),_mm256_set_epi64x((unsigned long long)(-1),(unsigned long long)(-1),0,0),
								_mm256_set_epi64x((unsigned long long)(-1),(unsigned long long)(-1),(unsigned long long)(-1),0) };

	__m256i blend_select4[4] = { _mm256_set1_epi64x(0), _mm256_set_epi64x(0,0,0,(unsigned long long)(-1)),_mm256_set_epi64x(0,0,(unsigned long long)(-1),(unsigned long long)(-1)),
								_mm256_set_epi64x(0,(unsigned long long)(-1),(unsigned long long)(-1),(unsigned long long)(-1)) };


#if __AVX512F__
	__m512i rot8l[8] = { _mm512_set_epi64(7,6,5,4,3,2,1,0),_mm512_set_epi64(6,5,4,3,2,1,0,7),_mm512_set_epi64(5,4,3,2,1,0,7,6),
						_mm512_set_epi64(4,3,2,1,0,7,6,5),_mm512_set_epi64(3,2,1,0,7,6,5,4),_mm512_set_epi64(2,1,0,7,6,5,4,3),_mm512_set_epi64(1,0,7,6,5,4,3,2),_mm512_set_epi64(0,7,6,5,4,3,2,1) };

	__m512i rot8r[8] = { _mm512_set_epi64(7,6,5,4,3,2,1,0), _mm512_set_epi64(0,7,6,5,4,3,2,1),_mm512_set_epi64(1,0,7,6,5,4,3,2),_mm512_set_epi64(2,1,0,7,6,5,4,3),
						_mm512_set_epi64(3,2,1,0,7,6,5,4),_mm512_set_epi64(4,3,2,1,0,7,6,5),_mm512_set_epi64(5,4,3,2,1,0,7,6),_mm512_set_epi64(6,5,4,3,2,1,0,7) };

	__mmask8 blend_fill8[8] = {__mmask8(0b00000000),__mmask8(0b10000000) ,__mmask8(0b11000000) ,__mmask8(0b11100000) ,__mmask8(0b11110000) ,__mmask8(0b11111000) ,__mmask8(0b11111100) ,__mmask8(0b11111110) };

	__mmask8 blend_select8[8] = { __mmask8(0b00000000),__mmask8(0b00000001) ,__mmask8(0b00000011) ,__mmask8(0b00000111) ,__mmask8(0b00001111) ,__mmask8(0b00011111) ,__mmask8(0b00111111) ,__mmask8(0b01111111) };
#endif
}


namespace norm_const {
	//divisor defined this way because normal distribution in range (0,1) is required for cdfnorminv 
	//static constexpr const float divisor32 = 1.0 / (4294967296+1); //2.328306366607658E-10;  //float: 1/4294967425=1/(2^32+129) to get smallest single precision value smaller 1 for random value 2^32 (max value +1 in order to get no 0) / usually: 1/4294967297 =1/(max value +2); 
	float divisor24 = 1.0 / (16777216+1);
	double divisor32_d = 1.0 / (4294967296 + 1);
	
	__m128i norm_shift128 = _mm_set1_epi32(8);
	__m256i norm_shift256 = _mm256_set1_epi32(8);

	//__m128 divisor128_32_ps = _mm_set1_ps(divisor32);
	//__m256 divisor256_32_ps = _mm256_set1_ps(divisor32);

	__m128 divisor128_24_ps = _mm_set1_ps(divisor24);
	__m256 divisor256_24_ps = _mm256_set1_ps(divisor24);

	__m128 one128_ps = _mm_set1_ps(1);
	__m256 one256_ps = _mm256_set1_ps(1);
	__m256d one256_pd = _mm256_set1_pd(1);

	__m128i one128_epi32 = _mm_set1_epi32(1);
	__m256i one256_epi32 = _mm256_set1_epi32(1);
	__m256i one256_epi64 = _mm256_set1_epi64x(1);

	__m128 min128_32_ps = _mm_set1_ps(2147483648);
	__m256 min256_32_ps = _mm256_set1_ps(2147483648);
	

	__m256d divisor256_64_pd = _mm256_set1_pd(divisor32_d);
	__m256d min256_32_pd = _mm256_set1_pd(2147483648.0);
#if __AVX512F__
	__m512d min512_32_pd = _mm512_set1_pd(2147483648.0);
	__m512d divisor512_64_pd = _mm512_set1_pd(divisor32_d);
	__m512d one512_pd = _mm512_set1_pd(1);
	__m512i norm_shift512 = _mm512_set1_epi32(8);
#endif
}
