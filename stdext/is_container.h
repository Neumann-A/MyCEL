///---------------------------------------------------------------------------------------------------
// file:		stdext\is_container.h
//
// summary: 	Declares the is container class
//
// Copyright (c) 2017 Alexander Neumann.
//
// author: Alexander
// date: 06.08.2017

#ifndef INC_is_container_H
#define INC_is_container_H
///---------------------------------------------------------------------------------------------------
#pragma once

//Sequence Containers
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

//Adaptors (For the seq. containers)
#include <stack>
#include <queue> //queue & priority_queue

//Associative Containers
#include <set> //set & multiset
#include <map> //map & multimatp 

//Unordered Versions
#include <unordered_set>
#include <unordered_map>

#include <type_traits>
#include <utility>

namespace stdext
{
	template<typename T, typename _ = void>
	struct is_container : std::false_type {};

	template<typename T>
	struct is_container<
		T,
		std::void_t<
		typename T::value_type,
		typename T::size_type,
		typename T::iterator,
		typename T::const_iterator,
		decltype(std::declval<T>().empty()),
		decltype(std::declval<T>().size()),
		decltype(std::declval<T>().begin()),
		decltype(std::declval<T>().end()),
		decltype(std::declval<T>().cbegin()),
		decltype(std::declval<T>().cend())
		>	> : public std::true_type{};

	template<typename T>
	static constexpr bool is_container_v = is_container<T>::value;

	namespace
	{
		static_assert(is_container_v<std::array<double,5>>);
		static_assert(is_container_v<std::vector<float>>);
		static_assert(is_container_v<std::deque<int>>);
		static_assert(is_container_v<std::list<std::uint16_t>>);
		static_assert(is_container_v<std::set<float>>);
		static_assert(is_container_v<std::multiset<float>>);
		static_assert(is_container_v<std::map<std::uint16_t,float>>);
		static_assert(is_container_v<std::multimap<std::uint16_t,float>>);
		static_assert(is_container_v<std::multiset<float>>);
		static_assert(is_container_v<std::unordered_set<float>>);
		static_assert(is_container_v<std::unordered_multiset<float>>);
		static_assert(is_container_v<std::unordered_map<std::uint16_t,float>>);
		static_assert(is_container_v<std::unordered_multimap<std::uint16_t,float>>);

		//These are not containers due to lack of some iterators or members! (They use one of the above internally but have a different interface!)
		static_assert(!is_container_v<std::forward_list<float>>); //Lacks size() method !
		static_assert(!is_container_v<std::stack<float>>);
		static_assert(!is_container_v<std::queue<float>>);
		static_assert(!is_container_v<std::priority_queue<float>>);
	}

	//specialize a type for all of the STL containers.
	namespace is_stl_container_impl {
		template <typename T>       struct is_stl_container :std::false_type {};
		template <typename T, std::size_t N> struct is_stl_container<std::array    <T, N>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::vector            <Args...>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::deque             <Args...>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::list              <Args...>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::forward_list      <Args...>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::set               <Args...>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::multiset          <Args...>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::map               <Args...>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::multimap          <Args...>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::unordered_set     <Args...>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::unordered_multiset<Args...>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::unordered_map     <Args...>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::unordered_multimap<Args...>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::stack             <Args...>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::queue             <Args...>> :std::true_type {};
		template <typename... Args> struct is_stl_container<std::priority_queue    <Args...>> :std::true_type {};
	}

	//type trait to utilize the implementation type traits as well as decay the type
	template <typename T> struct is_stl_container {
		static constexpr bool const value = is_stl_container_impl::is_stl_container<std::decay_t<T>>::value;
	};

}

#endif	// INC_is_container_H
// end of stdext\is_container.h
///---------------------------------------------------------------------------------------------------
