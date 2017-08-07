///---------------------------------------------------------------------------------------------------
// file:		stdext\is_nested_arithmetic_container.h
//
// summary: 	Declares the is nested arithmetic container class
//
// Copyright (c) 2017 Alexander Neumann.
//
// author: Alexander
// date: 06.08.2017

#ifndef INC_is_nested_arithmetic_container_H
#define INC_is_nested_arithmetic_container_H
///---------------------------------------------------------------------------------------------------
#pragma once

#include "is_nested_container.h"
#include "is_arithmetic_container.h"

#include <algorithm>
#include <functional>


namespace stdext
{
	template<typename T, typename _ = std::void_t<>>
	struct is_nested_arithmetic_container : std::false_type {};

	template<typename T>
	struct is_nested_arithmetic_container<T, std::void_t<typename std::decay_t<T>::value_type> >
		: std::conditional_t<is_nested_container_v<std::decay_t<typename std::decay_t<T>::value_type>>, is_nested_arithmetic_container<std::decay_t<typename std::decay_t<T>::value_type>>,std::is_arithmetic<typename std::decay_t<T>::value_type>> {};

	template<typename T>
	static constexpr bool is_nested_arithmetic_container_v = is_nested_arithmetic_container<T>::value;

	//using NestedContainer = std::vector<std::vector<std::vector<double>>>;
	using NestedContainer = std::vector<double>;
	static_assert(!is_arithmetic_container_v<NestedContainer>);
	static_assert(is_container_v<std::decay_t<NestedContainer>::value_type>);
	static_assert(is_nested_container_v<NestedContainer>);
	static_assert(is_nested_arithmetic_container_v<NestedContainer>);

	template<typename Container>
	std::enable_if_t<(is_nested_arithmetic_container_v<std::decay_t<Container>> || is_arithmetic_container_v<std::decay_t<Container>>), std::vector<std::size_t>> calcNestedContainerMaxDim(const Container& container)
	{
		using Contained = std::decay_t<typename std::decay_t<Container>::value_type>;

		if constexpr (is_arithmetic_container_v<Container>)
		{
			return { container.size() };
		}
		//else if constexpr(std::is_same_v<Contained, std::array<typename Contained::value_type, array_size<Contained>>>) //Contained is array
		//{
		//	maxlist.emplace_back(array_size<Contained>); // Array has one comparison less!
		//}
		else if constexpr(is_nested_arithmetic_container_v<Contained>)
		{
			std::size_t maxcontainedsize{ 0 };
			std::vector<std::size_t> maxlist;
			for (const auto &elem : container)
			{
				const auto listtocheck = calcNestedContMaxDim(elem);
				maxcontainedsize = (maxcontainedsize > elem.size()) ? maxcontainedsize : elem.size(); // We do not need this in the array case!
				if (tmpmaxlist.empty())
				{
					tmpmaxlist = listtocheck;
					continue;
				}
				constexpr auto binopmax = [](const std::size_t &a, const std::size_t &b) -> std::size_t { return std::max(a, b); };
				std::transform(tmpmaxlist.begin(), tmpmaxlist.end(), listtocheck.begin(), tmpmaxlist.begin(), binopmax);
			}
			maxlist.emplace_back(container.size());
		}
	};

}
#endif	// INC_is_nested_arithmetic_container_H
// end of stdext\is_nested_arithmetic_container.h
///---------------------------------------------------------------------------------------------------
