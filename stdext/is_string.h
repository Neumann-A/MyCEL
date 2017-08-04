#pragma once

#ifndef _IS_STRING_H
#define _IS_STRING_H

#include <type_traits>
#include <string>

namespace stdext
{

	//template<typename T>
	//struct is_string : std::false_type;
	
	template<typename T,
		typename CharT		= typename std::decay_t<T>::value_type,
		typename Traits		= typename std::decay_t<T>::traits_type,
		typename Allocator	= typename std::decay_t<T>::allocator_type>
	using is_string = std::is_same< std::decay_t<T>, std::basic_string<CharT, Traits, Allocator> >;
	
	template<typename T,
		typename CharT		= typename std::decay_t<T>::value_type,
		typename Traits		= typename std::decay_t<T>::traits_type,
		typename Allocator	= typename std::decay_t<T>::allocator_type>
	static constexpr bool is_string_v = is_string<T,CharT,Traits,Allocator>::value;

	//Tests
	//static_assert(stdext::is_string_v<std::string>);
	//static_assert(stdext::is_string_v<std::string&>);
	//static_assert(stdext::is_string_v<const std::string&>);
	//static_assert(stdext::is_string_v<volatile std::string&>);

}

#endif