#pragma once


#include <type_traits>

#include "is_container.h"
#include "is_string.h"


namespace stdext
{
	template<typename T, typename _ = std::void_t<> >
	struct is_arithmetic_container : std::false_type{};

	template <typename T>
	struct is_arithmetic_container<T,
		std::void_t< typename std::decay_t<T>::value_type >> : std::conjunction <  is_container< std::decay_t<T> >,
														std::negation< is_string<T> >,
		std::is_arithmetic< typename std::decay_t<T>::value_type > > {};
	template<typename T>
	static constexpr bool is_arithmetic_container_v = is_arithmetic_container<T>::value;


	//static_assert(is_arithmetic_container_v<std::vector<double>>);
	//static_assert(is_arithmetic_container_v<std::vector<double>&>);
	//static_assert(is_arithmetic_container_v<std::vector<std::string>>);
	//static_assert(is_arithmetic_container_v<std::string>);
	
}