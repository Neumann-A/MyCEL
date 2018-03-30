#pragma once

#ifndef INC_BASICINCLUDES_H_
#define INC_BASICINCLUDES_H_

#include <string>			// For Std::String
#include <sstream>			// For Std::sstream

#include <iomanip>			// For manipulation of streams
#include <iostream>			// std::cout ::err ::cin 

#include <typeinfo>			// Typeinformation
#include <type_traits>

#include <cmath>			// Math constants
#include <limits>			//limits of math constants

#include "BasicMacros.h"

namespace BasicTools
{
	// Nummeric Conversion for Integer Types to std::string
	template<typename INTEGER>
	std::enable_if_t<std::is_integral<INTEGER>::value, std::string> toStringScientific(const INTEGER& num)
	{
		//std::cout << "Integer conversion called" << std::endl;

		std::stringstream str;
		str << std::dec << num;
		return str.str();
		
	};

	// Nummeric Conversion for Floating Point Types to std::string
	template<typename FLOAT>
	std::enable_if_t<std::is_floating_point<FLOAT>::value, std::string> toStringScientific(const FLOAT& num)
	{
		//std::cout << "Float conversion called" << std::endl;

		std::stringstream str;
		str << std::scientific << num;
		return str.str();

	};

	// Conversion from a std::string to a arithmetic type
	template<typename Number>
	std::enable_if_t<std::is_arithmetic<Number>::value, std::decay_t<Number>> stringToNumber(const std::string&, size_t &)
	{
		//assert(false); // should not be called!
		return 0;
	};

	// Conversion from a std::string to a arithmetic type
	template<typename Number>
	std::enable_if_t<std::is_arithmetic<Number>::value> stringToNumber(const std::string& str, size_t &pos, Number& Return)
	{
		Return = stringToNumber<Number>(str, pos);
	}

	//Explicit instantiations
	template<>
	float stringToNumber<float>(const std::string& stringtoconvert, size_t& pos);
	template<>
	double stringToNumber<double>(const std::string& stringtoconvert, size_t& pos);
	template<>
	long double stringToNumber<long double>(const std::string& stringtoconvert, size_t& pos);

	template<>
	int stringToNumber<int>(const std::string& stringtoconvert, size_t& pos);
	template<>
	long stringToNumber<long>(const std::string& stringtoconvert, size_t& pos);

	template<>
	unsigned long stringToNumber<unsigned long>(const std::string& stringtoconvert, size_t& pos);
	template<>
	long long stringToNumber<long long>(const std::string& stringtoconvert, size_t& pos);
	template<>
	unsigned long long stringToNumber<unsigned long long>(const std::string& stringtoconvert, size_t& pos);

}

#endif //_BASICINCLUDES_H_
