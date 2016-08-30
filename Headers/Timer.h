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
	Timer() 
	{
		_times.push_back(clock::now());
	};
	~Timer() {};

	//Sets the start time to the 
	BASIC_ALWAYS_INLINE void start() noexcept
	{
		_time_begin = clock::now();
	};
	// Stops the time and returns the count() to the start time
	BASIC_ALWAYS_INLINE long long stop() noexcept
	{
		_time_end = clock::now();
		return (_time_end - _time_begin).count();
	};

	// Return Conversion Factor from Counts to Seconds
	BASIC_ALWAYS_INLINE long long CountsToSeconds() const noexcept
	{
		return static_cast<long long>(unit::period::den);
	}

	// Returns the unit conversion factor
	BASIC_ALWAYS_INLINE double unitFactor() const noexcept
	{
		double num = static_cast<double>(unit::period::num);
		double den = static_cast<double>(unit::period::den);
		return num/den;
	}

	//Starts a split time measurement 
	BASIC_ALWAYS_INLINE void startSplit() 
	{
		_times.clear();
		
		_times.push_back(clock::now());

	};

	// Takes a split time measurement and returns counts to last measurement
	BASIC_ALWAYS_INLINE long long takeSplit() 
	{
		auto it = _times.end();
		_times.push_back(clock::now());
		auto it2 = _times.end();
		return (*it2 - *it).count();
	};
	
	// Takes and stops a split time measurement and returns counts to last measurement
	BASIC_ALWAYS_INLINE long long stopSplit()
	{
		auto it = _times.end();
		_times.push_back(clock::now());
		auto it2 = _times.end();
		return (*it2 - *it).count();
	};

	// Returns all taken split times as timepoints. TODO why not only take the times?
	BASIC_ALWAYS_INLINE std::vector<std::chrono::time_point<clock, unit> > getSplits()
	{
		return _times;
	};
};


auto timeFunction = [](auto&& func, auto&&... params) // C++14
{
	Timer<> Timer;
	std::forward<decltype(func)>(func)( // invoke func
		std::forward<decltype(params)>(params)... // on params
		);
	auto Tmp = Timer.stop();
	Logger::Log("Function call needed "+std::to_string(Tmp*Timer.unitFactor()/1000)+"ms");
};



#endif	// INC_Timer_H
// end of Headers\Timer.h
///---------------------------------------------------------------------------------------------------
