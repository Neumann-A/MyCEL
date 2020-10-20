#pragma once

#include <cstddef>
#include <type_traits>

namespace boost
{
	template<typename T, std::size_t NumDims, typename Allocator>
		class multi_array;
}

namespace stdext
{
	template<typename T, typename _ = std::void_t<T>>
	struct is_boost_multiarray : std::false_type {};

	template<typename T, std::size_t NumDims, typename Allocator>
	struct is_boost_multiarray<boost::multi_array<T, NumDims, Allocator>> : std::true_type {};

	template<typename T>
	static constexpr bool is_boost_multiarray_v = is_boost_multiarray<T>::value;
}
