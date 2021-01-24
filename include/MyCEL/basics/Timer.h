///---------------------------------------------------------------------------------------------------
// file:		Headers\Timer.h
//
// summary: 	Declares the timer class
//
// Copyright (c) 2016 Alexander Neumann.
//
// author: Alexander Neumann
// date: 07.06.2016

#ifndef INC_Timer_H
#define INC_Timer_H
///---------------------------------------------------------------------------------------------------
#pragma once

#include <chrono>

#include <vector>

#include <iostream>
#include <sstream>
#include <type_traits>

#include "BasicMacros.h"
#include "Logger.h"
//TODO use standard duration casts?

///-------------------------------------------------------------------------------------------------
/// <summary>	Timer class for performance measurements. Could also be called StopWatch (C#) </summary>
///
/// <typeparam name="clock">	Type of the clock. (default: std::chrono::high_resolution_clock). </typeparam>
/// <typeparam name="unit"> 	Type of the unit (default: std::chrono::nanoseconds). </typeparam>
///-------------------------------------------------------------------------------------------------
template<typename clock = std::chrono::high_resolution_clock, typename unit = std::chrono::nanoseconds>
class Timer
{
private:
    std::chrono::time_point<clock, unit> _time_begin, _time_end;
    std::vector<std::chrono::time_point<clock, unit>> _times;
protected:
public:
    BASIC_ALWAYS_INLINE Timer() : _time_begin(clock::now()), _times({_time_begin}) {};
    BASIC_ALWAYS_INLINE ~Timer() {};

    //Sets the start time to the 
    BASIC_ALWAYS_INLINE void start() noexcept
    {
        _time_begin = clock::now();
    };

    // Stops the time and returns the count() to the start time
    BASIC_ALWAYS_INLINE auto stop() noexcept
    {
        _time_end = clock::now();
        return (_time_end - _time_begin).count();
    };

    // Return Conversion Factor from Counts to Seconds
    BASIC_ALWAYS_INLINE std::intmax_t CountsToSeconds() const noexcept
    {
        return static_cast<std::intmax_t>(unit::period::den);
    }

    // Returns the unit conversion factor
    BASIC_ALWAYS_INLINE BASIC_CONSTEXPR static double unitFactor() noexcept
    {
        const auto num = static_cast<double>(unit::period::num);
        const auto den = static_cast<double>(unit::period::den);
        return num/den;
    }

    //Starts a split time measurement 
    BASIC_ALWAYS_INLINE void startSplit() 
    {
        _times.clear();
        _times.push_back(clock::now());
    };

    // Takes a split time measurement and returns counts to last measurement
    BASIC_ALWAYS_INLINE auto takeSplit() 
    {
        auto it = _times.end();
        _times.push_back(clock::now());
        auto it2 = _times.end();
        return (*it2 - *it).count();
    };
    
    // Takes and stops a split time measurement and returns counts to last measurement
    BASIC_ALWAYS_INLINE auto stopSplit()
    {
        auto it = _times.end();
        _times.push_back(clock::now());
        auto it2 = _times.end();
        return (*it2 - *it).count();
    };

    // Returns all taken split times as timepoints. TODO why not only take the times?
    BASIC_ALWAYS_INLINE auto getSplits() const noexcept
    {
        return _times;
    };
};


/// <summary>	Lambda to time a Function Call (C++14). It returns the used time in seconds </summary>
const auto timeFunction = [](auto&& func, auto&&... params)
{
    auto begin = std::chrono::high_resolution_clock::now();
    std::forward<decltype(func)>(func)( // invoke func
        std::forward<decltype(params)>(params)... // on params
        );
    auto end = std::chrono::high_resolution_clock::now();

    constexpr auto unit = static_cast<double>(std::chrono::high_resolution_clock::period::num)/static_cast<double>(std::chrono::high_resolution_clock::period::den);
    
    return static_cast<double>((end-begin).count())*unit;
};


/// <summary> Returns a formated String for Logging\Debugging or other things for timeFunction </summary>
const auto timeFunctionString = [](const std::string& str, auto&& func, auto&&... params)
{
    auto begin = std::chrono::high_resolution_clock::now();
    std::forward<decltype(func)>(func)( // invoke func
        std::forward<decltype(params)>(params)... // on params
        );
    auto end = std::chrono::high_resolution_clock::now();

    constexpr auto unit = static_cast<double>(std::chrono::high_resolution_clock::period::num) / static_cast<double>(std::chrono::high_resolution_clock::period::den);
    auto time = static_cast<double>((end - begin).count())*unit;

    return (str + std::to_string(time*1000) + " ms.");
};


#endif	// INC_Timer_H
// end of Headers\Timer.h
///---------------------------------------------------------------------------------------------------
