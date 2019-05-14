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
#endif
}

namespace math
{
	/*std::enable_if_t<stdext::is_eigen_type_v<std::decay_t<In>>>*/

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
			const auto indata = input.derived().template packet<alignof(*(input.derived().data() + offset))>(offset);
			FullType rescos;
			const auto ressin = Eigen::internal::psincos(&rescos, indata);
			cosres.derived().template writePacket<alignof(*(cosres.derived().data() + offset))>(offset, rescos);
			sinres.derived().template writePacket<alignof(*(sinres.derived().data() + offset))>(offset, ressin);
			sincos_unroller<offset + elements_packed, Out, In>(sinres, cosres, input);
		}
		else if constexpr (remain >= elements_packed / 2)
		{
			const auto indata = Eigen::internal::evaluator<In>(input.derived()).template packet<alignof(*(input.derived().data() + offset)), HalfType>(offset);
			HalfType rescos;
			const auto ressin = Eigen::internal::psincos(&rescos, indata);
			Eigen::internal::evaluator<Out>(cosres.derived()).template writePacket<alignof(*(cosres.derived().data() + offset)), HalfType>(offset, rescos);
			Eigen::internal::evaluator<Out>(sinres.derived()).template writePacket<alignof(*(sinres.derived().data() + offset)), HalfType>(offset, ressin);
			sincos_unroller<offset + elements_packed/2, Out, In>(sinres, cosres, input);
		}
		else if constexpr (remain != 0) // Only if odd number of elements or AVX512
		{
			*(sinres.derived().data() + offset) = ::std::sin(*(input.derived().data() + offset));
			*(cosres.derived().data() + offset) = ::std::cos(*(input.derived().data() + offset));
			sincos_unroller<offset + 1, Out, In>(sinres, cosres, input);
		}
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
