///---------------------------------------------------------------------------------------------------
// file:		stdext\is_eigen3_type.h
//
// summary: 	Declares the is eigen 3 type class
//
// Copyright (c) 2017 Alexander Neumann.
//
// author: Alexander
// date: 06.08.2017

#ifndef INC_is_eigen3_type_H
#define INC_is_eigen3_type_H
///---------------------------------------------------------------------------------------------------
#pragma once

#include <type_traits>

#include <utility>

#include "is_container.h"

namespace Eigen
{
//#ifndef EIGEN_CORE_H
//	template<typename Derived> struct EigenBase;
//#endif
//#ifndef EIGEN_CXX11_TENSOR_TENSOR_H
//	template<typename Derived, int AccessLevel = 0> class TensorBase;
//#endif
}

namespace stdext
{
	template<typename T, typename _ = std::void_t<>>
	struct is_eigen_type : std::false_type {};

	template<typename T, typename _ = std::void_t<>>
	struct is_container_with_eigen_t : std::false_type {};

	template<typename T, typename _ = std::void_t<>>
	struct is_eigen_tensor : std::false_type {};
	
#ifdef EIGEN_CORE_H
	template<typename T>
	struct is_eigen_type<T> : std::is_base_of<Eigen::EigenBase<std::decay_t<T>>, std::decay_t<T>> {};
	
	//template<typename T>
	//struct is_eigen_tensor_type<T> : std::is_base_of<Eigen::TensorBase<std::decay_t<T>>, std::decay_t<T>> {};

	template<typename T>
	static constexpr bool is_eigen_type_v = is_eigen_type<T>::value;

	template<typename T>
	struct is_container_with_eigen_t<T, std::void_t<typename std::decay_t<T>::value_type>> : std::conjunction<stdext::is_container<std::decay_t<T>>, is_eigen_type<typename std::decay_t<T>::value_type>> {};

	template<typename T>
	static constexpr bool is_container_with_eigen_type_v = is_container_with_eigen_t<T>::value;
	
#ifdef EIGEN_CXX11_TENSOR_TENSOR_H
	template<typename T>
	struct is_eigen_tensor<T, std::void_t<typename T::Scalar, decltype(std::declval<T>().NumIndices) >> : std::is_base_of<Eigen::TensorBase<T>, T> {};

	template<typename T>
	static constexpr bool is_eigen_tensor_v = is_eigen_tensor<T>::value;

	namespace
	{

		static_assert(is_eigen_tensor_v<Eigen::Tensor<double, 2>>);

	}
#endif
#endif
}

#endif	// INC_is_eigen3_type_H
// end of stdext\is_eigen3_type.h
///---------------------------------------------------------------------------------------------------
