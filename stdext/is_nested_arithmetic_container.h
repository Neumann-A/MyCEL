///---------------------------------------------------------------------------------------------------
// file:		stdext\is_nested_arithmetic_container.h
//
// summary: 	Declares the is nested arithmetic container class
//
// Copyright (c) 2017 Alexander Neumann.
//
// author: Alexander
// date: 06.08.2017

#ifndef INC_is_nested_arithmetic_container_H
#define INC_is_nested_arithmetic_container_H
///---------------------------------------------------------------------------------------------------
#pragma once

#include "is_nested_container.h"
#include "is_arithmetic_container.h"

namespace stdext
{
	template<typename T, typename _ = std::void_t<>>
	struct is_nested_arithmetic_container : std::false_type {};

	template<typename T>
	struct is_nested_arithmetic_container<T, std::void_t<typename std::decay_t<T>::value_type> >
		: std::conditional<is_nested_container<typename std::decay_t<T>::value_type>::value, is_nested_arithmetic_container<typename std::decay_t<T>::value_type>,std::is_arithmetic<typename std::decay_t<T>::value_type>> {};

	template<typename T>
	static constexpr bool is_nested_arithmetic_container_v = is_nested_arithmetic_container<T>::value;

	using NestedContainer = std::vector<std::vector<std::vector<double>>>;
	static_assert(!is_arithmetic_container_v<NestedContainer>);
	static_assert(is_container_v<std::decay_t<NestedContainer>::value_type>);
	static_assert(is_nested_arithmetic_container_v<NestedContainer>);

}
#endif	// INC_is_nested_arithmetic_container_H
// end of stdext\is_nested_arithmetic_container.h
///---------------------------------------------------------------------------------------------------
