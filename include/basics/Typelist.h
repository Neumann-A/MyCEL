///---------------------------------------------------------------------------------------------------
// file:		Headers\Typelist.h
//
// summary: 	Declares the typelist class
//
// Copyright (c) 2017 Alexander Neumann.
//
// author: Alexander Neumann
// date: 08.01.2017

#ifndef INC_Typelist_H
#define INC_Typelist_H
///---------------------------------------------------------------------------------------------------
#pragma once

#include <cinttypes>

///-------------------------------------------------------------------------------------------------
/// <signature>	Namespace Basics. </signature>
///
/// <summary> Namespace for Basic and properly often used stuff. Used for general programming stuff
/// 		  which is not too specific about implementation details and other things</summary>
///-------------------------------------------------------------------------------------------------
namespace Basics
{
	class EndOfList {};
	class NoList {};

	template<typename Head, typename ...Args>
	class Typelist
	{
	public:
		using FirstType = Head;
		using TailList = Typelist<Args...>;
		using NextType = TailList::Head;

		static constexpr size_t TypeCount{ 1 + sizeof...(Args) };
	};

	template<typename Head>
	class Typelist
	{
	public:
		using FirstType = Head;
		using TailList = Typelist<EndOfList>;
		using NextType = EndOfList;

		static constexpr size_t TypeCount{ 1 };
	};

	template<>
	class Typelist<EndOfList>
	{
	public:
		static constexpr size_t TypeCount{ 0 };
	};
}





#endif	// INC_Typelist_H
// end of Headers\Typelist.h
///---------------------------------------------------------------------------------------------------
