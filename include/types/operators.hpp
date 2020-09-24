///---------------------------------------------------------------------------------------------------
// file:		operators.h
//
// summary: 	Declares templates for operatos used by strongtype
//
// Copyright (c) 2019 Alexander Neumann.
//
// author: Neumann
// date: 16.10.2019

#ifndef INC_operators_H
#define INC_operators_H
///---------------------------------------------------------------------------------------------------
#pragma once

#include <type_traits>

namespace
{
    template <typename T, template <typename> class CrtpType>
    struct CRTP
    {
        inline constexpr T& underlying() noexcept { return static_cast<T&>(*this); }
        inline constexpr T const& underlying() const noexcept { return static_cast<T const&>(*this); }
    };
}

//namespace util::type
//{
    template <typename T>
    struct Increment : CRTP<T, Increment>
    {
        inline constexpr T& operator++(int)
            noexcept(noexcept(this->underlying().get()++ ))
        {
            this->underlying().get()++; return this->underlying();
        }
    };

    template <typename T>
    struct PreIncrement : CRTP<T, PreIncrement>
    {
        inline constexpr T& operator++() 
            noexcept(noexcept(++this->underlying().get())) 
        { ++this->underlying().get(); return this->underlying(); }
    };

    template <typename T>
    struct Decrement : CRTP<T, Decrement>
    {
        inline constexpr T& operator--(int)
            noexcept(noexcept(this->underlying().get()--))
        {
            this->underlying().get()--; return this->underlying();
        }
    };

    template <typename T>
    struct PreDecrement : CRTP<T, PreDecrement>
    {
        inline constexpr T& operator--()
            noexcept(noexcept(--this->underlying().get()))
        {
            --this->underlying().get(); return this->underlying();
        }
    };

    template <typename T, typename U = T>
    struct AddAssign : CRTP<T, AddAssign>
    {
        inline constexpr T& operator+=(U const& other)
            noexcept(noexcept(this->underlying().get() += other))
        {
            this->underlying().get() += other; return this->underlying();
        }
    };


    template <typename R, typename T = R, typename U = T>
    struct Add : CRTP<T, Add>
    {
        inline constexpr R operator+(U const& other) const 
            noexcept(noexcept(R(this->underlying().get() + other)))  
        { return R(this->underlying().get() + other); }
    };

    template <typename T, typename U = T>
    struct SubstractAssign : CRTP<T, SubstractAssign>
    {
        inline constexpr T& operator-=(U const& other)
            noexcept(noexcept(this->underlying().get() -= other))
        {
            this->underlying().get() -= other; return this->underlying();
        }
    };

    template <typename R, typename T = R, typename U = T>
    struct Subtract : CRTP<T, Subtract>
    {
        inline constexpr R operator-(U const& other) const
            noexcept(noexcept(R(this->underlying().get() - other)))
        {
            return R(this->underlying().get() - other);
        }
    };

    template <typename T, typename U = T>
    struct MultiplyAssign : CRTP<T, MultiplyAssign>
    {
        inline constexpr T& operator*=(T const& other)
            noexcept(noexcept(this->underlying().get() *= other))
        {
            this->underlying().get() *= other; return this->underlying();
        }
    };

    template <typename R, typename T = R, typename U = T>
    struct Multiply : CRTP<T, Multiply>
    {
        inline constexpr R operator*(U const& other) const
            noexcept(noexcept(R(this->underlying().get() * other)))
        {
            return R(this->underlying().get() * other);
        }
    };

    template <typename T, typename U = T>
    struct DivideAssign : CRTP<T, DivideAssign>
    {
        inline constexpr T& operator/=(U const& other)
            noexcept(noexcept(this->underlying().get() /= other))
        {
            this->underlying().get() /= other; return this->underlying();
        }
    };

    template <typename R, typename T = R, typename U = T>
    struct Divide : CRTP<T, Divide>
    {
        inline constexpr R operator/(U const& other) const
            noexcept(noexcept(R(this->underlying().get() / other)))
        {
            return R(this->underlying().get() / other);
        }
    };

    template <typename T>
    struct Negate : CRTP<T, Negate>
    {
        inline constexpr T operator-() const 
            noexcept(noexcept(T{ -this->underlying().get() })) 
        { 
            return { -this->underlying().get() }; 
        }
    };

    template <typename T>
    struct ArrayAccess : CRTP<T, ArrayAccess>
    {
        inline constexpr T& operator[](std::size_t idx)  noexcept(noexcept(this->underlying().get()[idx]))  { return this->underlying().get()[idx]; }
        inline constexpr const T& operator[](std::size_t idx) const noexcept(noexcept(this->underlying().get()[idx])) { return this->underlying().get()[idx]; }
    };

    // This next are handled by the converion to the underlying type. 
    //template <typename T>
    //struct Compare
    //{
    //	inline constexpr bool operator<(T const& other) const { return *this < other; }
    //	inline constexpr bool operator>(T const& other) const { return other < *this; }
    //	inline constexpr bool operator<=(T const& other) const { return !(*this > other); }
    //	inline constexpr bool operator>=(T const& other) const { return !(*this < other); }
    //	inline constexpr bool operator==(T const& other) const { return !(*this < other || *this > other); }
    //	inline constexpr bool operator!=(T const& other) const { return !(*this == other); }
    //};

    //template <typename Destination>
    //struct ImplicitlyConversionTo
    //{
    //	template <typename T>
    //	struct templ
    //	{
    //		operator Destination() const
    //		{
    //			return *this.value;
    //		}
    //	};
    //};

    //template<typename NamedType_>
    //struct FunctionCallable;

    //template <typename T, typename Parameter, template<typename> class... Skills>
    //struct FunctionCallable<NamedType<T, Parameter, Skills...>> : crtp<NamedType<T, Parameter, Skills...>, FunctionCallable>
    //{
    //	operator T const& () const
    //	{
    //		return this->underlying().get();
    //	}
    //	operator T& ()
    //	{
    //		return this->underlying().get();
    //	}
    //};

    //template<typename NamedType_>
    //struct MethodCallable;

    //template <typename T, typename Parameter, template<typename> class... Skills>
    //struct MethodCallable<NamedType<T, Parameter, Skills...>>
    //{
    //	T const* operator->() const { return std::addressof(*this.value); }
    //	T* operator->() { return std::addressof(*this.value); }
    //};

    //template<typename NamedType_>
    //struct Callable : FunctionCallable<NamedType_>, MethodCallable<NamedType_> {};

#endif	// INC_operators_H
// end of operators.h
///---------------------------------------------------------------------------------------------------
