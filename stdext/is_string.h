///---------------------------------------------------------------------------------------------------
// file:		stdext\is_string.h
//
// summary: 	Declares the is string class
//
// Copyright (c) 2017 Alexander Neumann.
//
// author: Alexander
// date: 06.08.2017

#ifndef INC_is_string_H
#define INC_is_string_H
///---------------------------------------------------------------------------------------------------
#pragma once

#ifndef STDEXT_IS_STRING_H
#define STDEXT_IS_STRING_H

#include <type_traits>
#include <string>

namespace stdext
{
	template<typename T, typename _ = std::void_t<> >
	struct is_string : std::false_type {};

	template<typename CharT, typename TraitsT, typename AllocatorT>
	struct is_string<std::basic_string<CharT, TraitsT, AllocatorT>> : std::true_type {};
	
	//template <typename T>
	//struct is_string<T,
	//	std::void_t<
	//	typename std::decay_t<T>::value_type,
	//	typename std::decay_t<T>::traits_type,
	//	typename std::decay_t<T>::allocator_type
	//	>
	//>
	//	: std::is_same<
	//	std::basic_string<
	//	typename std::decay_t<T>::value_type,
	//	typename std::decay_t<T>::traits_type,
	//	typename std::decay_t<T>::allocator_type
	//	>,
	//	std::decay_t<T>
	//	>
	//{};

	template<typename T>
	constexpr bool is_string_v = is_string<T>::value;

	template<typename T, typename _ = std::void_t<> >
	struct is_container_of_strings : std::false_type {};

	template<typename T>
	struct is_container_of_strings<T, std::void_t<typename T::value_type>> : std::conjunction<stdext::is_string<std::decay_t<typename T::value_type>>,stdext::is_container<std::decay_t<T>>> {};
	
	template<typename T>
	constexpr bool is_container_of_strings_v = is_container_of_strings<T>::value;

	////Tests
	//static_assert(stdext::is_string_v<std::string>);
	//static_assert(stdext::is_string_v<std::string&>);
	//static_assert(stdext::is_string_v<const std::string&>);
	//static_assert(stdext::is_string_v<volatile std::string&>);

}

#endif

#endif	// INC_is_string_H
// end of stdext\is_string.h
///---------------------------------------------------------------------------------------------------
