#pragma once

#ifndef INC_GLOBALPARAMETERS_H_
#define INC_GLOBALPARAMETERS_H_

#ifdef _MSC_VER
#include <experimental/filesystem>
#else
#include <filesystem>
#endif

class GlobalParameters
{
protected:
	GlobalParameters() = default;
public:
	static std::experimental::filesystem::path Path;
};

#endif //_GLOBALPARAMETERS_H_
