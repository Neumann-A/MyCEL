#pragma once

#include <type_traits>

#include "is_container.h"

namespace stdext
{
	template<typename T, typename _ = void>
	struct is_associative_container : std::false_type {};
	
	template<typename T>
	struct is_associative_container<T, std::void_t<typename T::key_type> > : is_container<T>{};

	template<typename T>
	static constexpr bool is_associative_container_v = is_associative_container<T>::value;
}