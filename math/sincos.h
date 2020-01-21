///---------------------------------------------------------------------------------------------------
// file:		math\sincos.h
//
// summary: 	provides sincos functionallity
//
// Copyright (c) 2019 Alexander Neumann.
//
// author: Neumann
// date: 14.05.2019
#pragma once
#ifndef INC_sincos_H
#define INC_sincos_H
///---------------------------------------------------------------------------------------------------

#include <cstdint>
#include <cmath>
#include <immintrin.h>

#ifdef __clang__
#include "../intrin/svml_prolog.h"
#include "../intrin/svml/avx_svml_intrin.h"
#ifdef __AVX512__
#include "../intrin/svml/avx512_svml_intrin.h"
#endif
#endif

#include "../stdext/is_eigen3_type.h"
#include <Eigen/Core>

#ifdef EIGEN_CORE_H
namespace Eigen::internal {
	template<typename T> EIGEN_STRONG_INLINE T psincos(T* cosres, const T& In) {};

	template<> EIGEN_STRONG_INLINE Packet2d psincos(Packet2d* cosres, const Packet2d& Input)
	{
		return _mm_sincos_pd(cosres, Input);
	}
	template<> EIGEN_STRONG_INLINE Packet4f psincos(Packet4f* cosres, const Packet4f& Input)
	{
		return _mm_sincos_ps(cosres, Input);
	}

	template<> EIGEN_STRONG_INLINE Packet4d psincos(Packet4d* cosres, const Packet4d& Input)
	{
		return _mm256_sincos_pd(cosres, Input);
	}
	template<> EIGEN_STRONG_INLINE Packet8f psincos(Packet8f* cosres, const Packet8f& Input)
	{
		return _mm256_sincos_ps(cosres, Input);
	}

#ifdef __AVX512__
	template<> EIGEN_STRONG_INLINE Packet8d psincos(Packet8d* cosres, const Packet8d& Input)
	{
		return _mm512_sincos_pd(cosres, Input);
	}
	template<> EIGEN_STRONG_INLINE Packet16f psincos(Packet16f* cosres, const Packet16f& Input)
	{
		return _mm512_sincos_ps(cosres, Input);
	}

	template<> EIGEN_STRONG_INLINE Packet8d psincos_mask(Packet8d* cosres const Packet8d& sinmask, const Packet8d& cosmask, __mmask8 mask, const Packet8d& Input)
	{
		return _mm512_mask_sincos_pd(cosres, sinmask, cosmask, mask, Input);
	}
	template<> EIGEN_STRONG_INLINE Packet16f psincos_mask(Packet16f* cosres const Packet16f& sinmask, const Packet16f& cosmask, __mmask16 mask, const Packet16f& Input)
	{
		return _mm512_mask_sincos_ps(cosres, sinmask, cosmask, mask, Input);
	}
#endif
}



namespace math
{
	/*std::enable_if_t<stdext::is_eigen_type_v<std::decay_t<In>>>*/
	template<typename precision>
	struct mask_type_selector {
		using type = std::enable_if_t<!std::is_floating_point<precision>::value>;
	};

	template<>
	struct mask_type_selector<double>
	{
		using uint_t = std::uint8_t;
		using int_t = std::int8_t;
#ifdef __AVX512F__
		using mask_t = __mmask8;
#endif
	};

	template<>
	struct mask_type_selector<float>
	{
		using uint_t = std::uint16_t;
		using int_t = std::int16_t;
#ifdef __AVX512F__
		using mask_t = __mmask16;
#endif
	};

	template<int offset, typename Out, typename In>
	void sincos_unroller(Eigen::EigenBase<Out>& sinres, Eigen::EigenBase<Out>& cosres, const Eigen::EigenBase<In>& input)
	{
		using FullType = typename Eigen::internal::packet_traits<typename In::Scalar>::type;
		using HalfType = typename Eigen::internal::packet_traits<typename In::Scalar>::half;

		constexpr const auto size = In::RowsAtCompileTime * In::ColsAtCompileTime;
		constexpr const auto elements_packed = Eigen::internal::packet_traits<typename In::Scalar>::size;
		constexpr const auto remain = size - offset;

		if constexpr (remain >= elements_packed)
		{
			const auto indata = input.derived().template packet<alignof(decltype(*(input.derived().data())))>(offset);
			FullType rescos;
			const auto ressin = Eigen::internal::psincos(&rescos, indata);
			cosres.derived().template writePacket<alignof(decltype(*cosres.derived().data()))>(offset, rescos);
			sinres.derived().template writePacket<alignof(decltype(*sinres.derived().data()))>(offset, ressin);
			sincos_unroller<offset + elements_packed, Out, In>(sinres, cosres, input);
		}
#ifndef __AVX512__
		else if constexpr (remain >= elements_packed / 2)
		{
			const auto indata = Eigen::internal::evaluator<In>(input.derived()).template packet<alignof(decltype (*(input.derived().data() ))), HalfType>(offset);
			HalfType rescos;
			const auto ressin = Eigen::internal::psincos(&rescos, indata);
			Eigen::internal::evaluator<Out>(cosres.derived()).template writePacket<alignof(decltype (*(cosres.derived().data() ))), HalfType>(offset, rescos);
			Eigen::internal::evaluator<Out>(sinres.derived()).template writePacket<alignof(decltype (*(sinres.derived().data() ))), HalfType>(offset, ressin);
			sincos_unroller<offset + elements_packed/2, Out, In>(sinres, cosres, input);
		}
		else if constexpr (remain != 0) // Only if odd number of elements or AVX512
		{
			*(sinres.derived().data() + offset) = ::std::sin(*(input.derived().data() + offset));
			*(cosres.derived().data() + offset) = ::std::cos(*(input.derived().data() + offset));
			sincos_unroller<offset + 1, Out, In>(sinres, cosres, input);
		}
#else
		else if constexpr (remain != 0) // Only if odd number of elements or AVX512
		{
			constexpr mask_type_selector<typename In::Scalar>::uint_t uint_mask = -1;
			mask = uint_mask >> (elements_packed - remain);
			constexpr mask_type_selector<typename In::Scalar>::mask_t mask = (mask_type_selector<typename In::Scalar>::mask_t)uint_mask;
			const auto indata = input.derived().template packet<alignof(*(input.derived().data() + offset))>(offset);
			FullType rescos;
			const auto ressin = Eigen::internal::psincos(&rescos, indata, indata, mask, indata);
			cosres.derived().template writePacket<alignof(*(cosres.derived().data() + offset))>(offset, rescos);
			sinres.derived().template writePacket<alignof(*(sinres.derived().data() + offset))>(offset, ressin);
		}
#endif
		else
		{
			
			//Finsihed
		}
	}

	template<typename Out, typename In>
	void sincos(Eigen::EigenBase<Out>& sinres, Eigen::EigenBase<Out>& cosres, const Eigen::EigenBase<In>& input)
	{
		static_assert(In::RowsAtCompileTime * In::ColsAtCompileTime == Out::RowsAtCompileTime * Out::ColsAtCompileTime);

		constexpr const std::int64_t size = In::RowsAtCompileTime * In::ColsAtCompileTime;

		sincos_unroller<0, Out, In>(sinres, cosres, input);
		//while (offset < size)
		//{
		//	if (remaining >= elements_packed)
		//	{
		//		const auto indata = input.derived().template packet<alignof(*(input.derived().data() + offset))>(offset);
		//		FullType rescos;
		//		const auto ressin = Eigen::internal::psincos(&rescos, indata);
		//		cosres.derived().template writePacket<alignof(*(cosres.derived().data() + offset))>(offset, rescos);
		//		sinres.derived().template writePacket<alignof(*(cosres.derived().data() + offset))>(offset, ressin);
		//		remaining = remaining - elements_packed;
		//		offset += elements_packed;
		//	}

		//	if (remaining >= elements_packed / 2)
		//	{
		//		const auto indata = Eigen::internal::evaluator<In>(input.derived()).template packet<alignof(*(input.derived().data() + offset)), HalfType>(offset);
		//		HalfType rescos;
		//		const auto ressin = Eigen::internal::psincos(&rescos, indata);
		//		Eigen::internal::evaluator<Out>(cosres.derived()).template writePacket<alignof(*(cosres.derived().data() + offset)), HalfType>(offset, rescos);
		//		Eigen::internal::evaluator<Out>(sinres.derived()).template writePacket<alignof(*(sinres.derived().data() + offset)), HalfType>(offset, ressin);
		//		remaining = remaining - (elements_packed / 2);
		//		offset += elements_packed / 2;
		//	}

		//	if (offset < size);
		//	{
		//		*(cosres.derived().data() + offset) = ::std::cos(*(input.derived().data() + offset));
		//		*(sinres.derived().data() + offset) = ::std::sin(*(input.derived().data() + offset));
		//		offset += 1;
		//	}
		//}
	}
}
#endif

#endif	// INC_sincos_H
// math\sincos.h
///---------------------------------------------------------------------------------------------------
