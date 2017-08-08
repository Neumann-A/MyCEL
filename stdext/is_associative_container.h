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

	namespace
	{
		static_assert(!is_associative_container_v<std::array<double, 5>>);
		static_assert(!is_associative_container_v<std::vector<float>>);
		static_assert(!is_associative_container_v<std::deque<int>>);
		static_assert(!is_associative_container_v<std::list<std::uint16_t>>);

		//
		static_assert(is_associative_container_v<std::set<float>>);
		static_assert(is_associative_container_v<std::multiset<float>>);
		static_assert(is_associative_container_v<std::map<std::uint16_t, float>>);
		static_assert(is_associative_container_v<std::multimap<std::uint16_t, float>>);
		static_assert(is_associative_container_v<std::multiset<float>>);
		static_assert(is_associative_container_v<std::unordered_set<float>>);
		static_assert(is_associative_container_v<std::unordered_multiset<float>>);
		static_assert(is_associative_container_v<std::unordered_map<std::uint16_t, float>>);
		static_assert(is_associative_container_v<std::unordered_multimap<std::uint16_t, float>>);

		//These are not containers due to lack of some iterators or members! (They use one of the above internally but have a different interface!)
		static_assert(!is_associative_container_v<std::forward_list<float>>); //Lacks size() method !
		static_assert(!is_associative_container_v<std::stack<float>>);
		static_assert(!is_associative_container_v<std::queue<float>>);
		static_assert(!is_associative_container_v<std::priority_queue<float>>);
	}

}