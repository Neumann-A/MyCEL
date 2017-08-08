#pragma once

#include <type_traits>
#include <utility>

#include "is_container.h"

namespace stdext
{
	template<typename T, typename _ = void>
	struct is_memory_sequentiel_container : std::false_type {};

	template<typename T>
	struct is_memory_sequentiel_container<T, std::void_t<decltype(std::declval<T>().data())> > : std::conjunction< is_container<T> , std::negation<is_container<typename T::value_type> > > {};
	//Nested Containers will most likly not be memory sequentiel. Else use a partial specialization for the type

	template<typename T>
	static constexpr bool is_memory_sequentiel_container_v = is_memory_sequentiel_container<T>::value;

	namespace
	{
		using MemSeq1 = std::vector<double>;
		using MemSeq2 = std::array<float,20>;
		using MemSeq3 = std::vector<std::uint16_t>;
		using NotMemSeq = std::list<std::uint64_t>;
		using NotMemSeq2 = std::vector<MemSeq2>;

		static_assert(is_memory_sequentiel_container_v<MemSeq1>);
		static_assert(is_memory_sequentiel_container_v<MemSeq2>);
		static_assert(is_memory_sequentiel_container_v<MemSeq3>);

		static_assert(!is_memory_sequentiel_container_v<NotMemSeq>);
		static_assert(!is_memory_sequentiel_container_v<NotMemSeq2>);
	}
}