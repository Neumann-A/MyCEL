#pragma once

#ifndef _IS_STRING_H
#define _IS_STRING_H

#include <type_traits>
#include <string>

namespace stdext
{
	template< class, class = std::void_t<> >
	struct has_value_type_t : std::false_type { };
	template< class T >
	struct has_value_type_t<T, std::void_t<typename T::value_type>> : std::true_type { };

	template< class, class = std::void_t<> >
	struct has_traits_type_t : std::false_type { };
	template< class T >
	struct has_traits_type_t<T, std::void_t<typename T::traits_type>> : std::true_type { };

	template< class, class = std::void_t<> >
	struct has_allocator_type_t : std::false_type { };
	template< class T >
	struct has_allocator_type_t<T, std::void_t<typename T::allocator_type>> : std::true_type { };
		
	//template<typename T,
	//	typename CharT		= typename std::decay_t<T>::value_type,
	//	typename Traits		= typename std::decay_t<T>::traits_type,
	//	typename Allocator	= typename std::decay_t<T>::allocator_type>
	//using is_string = std::is_same< std::decay_t<T>, std::basic_string<CharT, Traits, Allocator> >;
	
	template<typename T, typename _ = std::void_t<> >
	struct is_string : std::false_type {};

	template<typename CharT, typename TraitsT, typename AllocatorT>
	struct is_string<std::basic_string<CharT, TraitsT, AllocatorT>> : std::true_type {};
	
	template <typename T>
	struct is_string<T,
		std::void_t<
		typename std::decay_t<T>::value_type,
		typename std::decay_t<T>::traits_type,
		typename std::decay_t<T>::allocator_type
		>
	>
		: std::is_same<
		std::basic_string<
		typename std::decay_t<T>::value_type,
		typename std::decay_t<T>::traits_type,
		typename std::decay_t<T>::allocator_type
		>,
		std::decay_t<T>
		>
	{};

	template<typename T>
	constexpr bool is_string_v = is_string<T>::value;

	////Tests
	//static_assert(stdext::is_string_v<std::string>);
	//static_assert(stdext::is_string_v<std::string&>);
	//static_assert(stdext::is_string_v<const std::string&>);
	//static_assert(stdext::is_string_v<volatile std::string&>);

}

#endif