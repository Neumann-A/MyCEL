///---------------------------------------------------------------------------------------------------
// file:		stdext\is_nested_container.h
//
// summary: 	Declares the is nested container class
//
// Copyright (c) 2017 Alexander Neumann.
//
// author: Alexander
// date: 06.08.2017

#ifndef INC_is_nested_container_H
#define INC_is_nested_container_H
///---------------------------------------------------------------------------------------------------
#pragma once

#include "is_container.h"
#include "get_array_size.h"

namespace stdext
{
	template<typename T, typename _ = std::void_t<>>
	struct is_nested_container : std::false_type {};

	template<typename T>
	struct is_nested_container<T, std::void_t<typename std::decay_t<T>::value_type> >
		: std::conjunction<is_container<std::decay_t<T>>,is_container<std::decay_t<typename std::decay_t<T>::value_type>>> {};

	template<typename T>
	static constexpr bool is_nested_container_v = is_nested_container<T>::value;

	template<typename T, typename _ = std::void_t<>>
	struct get_nested_arithmetic_type_helper
	{
		using type = typename std::decay<T>::value_type;
	};

	template<typename T, typename _ = std::void_t<>>
	struct get_nested_type 
	{
		using type = T;
	};

	template<typename T>
	struct get_nested_type_helper 
	{
		using type = T;
	};

	template<typename T>
	struct get_nested_type<T, std::void_t<typename std::decay_t<T>::value_type>> :
		std::conditional_t<is_container_v<T>, get_nested_type<typename std::decay_t<T>::value_type>, get_nested_type_helper<T>>
	{};

	template<typename T>
	using get_nested_type_t = typename get_nested_type<T>::type;

	namespace
	{
		using NestedContainer = std::vector<std::array<std::vector<double>,5>>;
		static_assert(is_container_v<NestedContainer>);
		static_assert(is_container_v<std::decay_t<NestedContainer>::value_type>);
		static_assert(is_nested_container_v<NestedContainer>);
		static_assert(std::is_same_v<double, get_nested_type_t<NestedContainer>>);

		using IsNotNested = std::vector<double>;

		static_assert(is_container_v<IsNotNested>);
		static_assert(!is_container_v<std::decay_t<IsNotNested>::value_type>);
		static_assert(!is_nested_container_v<IsNotNested>);
		static_assert(std::is_same_v<double, get_nested_type_t<IsNotNested>>);
	}
	

};
#endif	// INC_is_nested_container_H
// end of stdext\is_nested_container.h
///---------------------------------------------------------------------------------------------------
