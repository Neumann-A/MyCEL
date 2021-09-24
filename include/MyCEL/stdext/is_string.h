///---------------------------------------------------------------------------------------------------
// file:		stdext\is_string.h
//
// summary: 	Declares the is string class
//
// Copyright (c) 2017 Alexander Neumann.
//
// author: Alexander
// date: 06.08.2017

#ifndef INC_is_string_H
#define INC_is_string_H
///---------------------------------------------------------------------------------------------------
#pragma once

#ifndef STDEXT_IS_STRING_H
#define STDEXT_IS_STRING_H

#include <type_traits>
#include <string>

#include "is_container.h"

namespace stdext
{
    namespace detail
    {
        template<typename T, typename _ = std::void_t<> >
        struct is_string_impl : std::false_type {};

        template<typename CharT, typename TraitsT, typename AllocatorT>
        struct is_string_impl<std::basic_string<CharT, TraitsT, AllocatorT>> : std::true_type {};
    }

    template <typename T>
    struct is_string :  detail::is_string_impl<std::remove_cvref_t<T>> {};

    template<typename T>
    constexpr bool is_string_v = is_string<T>::value;

    template<typename T, typename _ = std::void_t<> >
    struct is_container_of_strings : std::false_type {};

    template<typename T>
    struct is_container_of_strings<T, std::void_t<typename T::value_type>> : 
            std::conjunction<stdext::is_string<std::remove_cvref_t<typename T::value_type>>,
                           stdext::is_container<std::remove_cvref_t<T>>>
    {
    };
    
    template<typename T>
    constexpr bool is_container_of_strings_v = is_container_of_strings<T>::value;
}

#endif

#endif	// INC_is_string_H
// end of stdext\is_string.h
///---------------------------------------------------------------------------------------------------
