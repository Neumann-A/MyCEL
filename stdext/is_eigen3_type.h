#pragma once

//std::enable_if_t<std::conjunction<stdext::is_container<std::decay_t<T>>,
//	is_eigen_t<std::decay_t<T>>,
//	std::decay_t<typename T::value_type>>>::value

//std::enable_if_t<std::conjunction<stdext::is_container<std::decay_t<T>>,
//	std::is_base_of<Eigen::EigenBase<std::decay_t<typename T::value_type>>,
//	std::decay_t<typename T::value_type>>>::value


#include <type_traits>

#include "is_container.h"

namespace Eigen
{
	template<typename Derived> struct EigenBase;
}

namespace stdext
{
	template<typename T, typename _ = std::void_t<>>
	struct is_eigen_t : std::false_type {};


	template<typename T, typename _ = std::void_t<>>
	struct is_container_with_eigen_t : std::false_type {};
	
	template<typename T>
	struct is_eigen_t<T> : std::is_base_of<Eigen::EigenBase<std::decay_t<T>>, std::decay_t<T>> {};
	
	template<typename T>
	static constexpr bool is_eigen_type_v = is_eigen_t<T>::value;

	template<typename T>
	struct is_container_with_eigen_t<T, std::void_t<typename std::decay_t<T>::value_type>> : std::conjunction<stdext::is_container<std::decay_t<T>>, is_eigen_t<typename std::decay_t<T>::value_type>> {};

	template<typename T>
	static constexpr bool is_container_with_eigen_type_v = is_container_with_eigen_t<T>::value;
}