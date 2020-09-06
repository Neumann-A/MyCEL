///---------------------------------------------------------------------------------------------------
// file:		C:\Sources\Repos\Everything\Basic_Library\basics\GlobalParameters.h
//
// summary: 	Declares the global parameters class
//
// Copyright (c) 2019 Alexander Neumann.
//
// author: Neumann
// date: 04.04.2019

#ifndef INC_GlobalParameters_H
#define INC_GlobalParameters_H
///---------------------------------------------------------------------------------------------------
#pragma once

#ifndef INC_GLOBALPARAMETERS_H_
#define INC_GLOBALPARAMETERS_H_

#include <filesystem>

class GlobalParameters
{
protected:
	GlobalParameters() = default;
public:
	static std::filesystem::path Path;
};

#endif //_GLOBALPARAMETERS_H_

#endif	// INC_GlobalParameters_H
// end of C:\Sources\Repos\Everything\Basic_Library\basics\GlobalParameters.h
///---------------------------------------------------------------------------------------------------
