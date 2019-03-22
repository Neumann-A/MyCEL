#pragma once

#ifndef INC_GLOBALPARAMETERS_H_
#define INC_GLOBALPARAMETERS_H_

#ifdef _MSC_VER
#include <filesystem>
#else
#include <filesystem>
#endif

class GlobalParameters
{
protected:
	GlobalParameters() = default;
public:
	static std::filesystem::path Path;
};

#endif //_GLOBALPARAMETERS_H_
