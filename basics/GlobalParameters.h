#pragma once

#ifndef _GLOBALPARAMETERS_H_
#define _GLOBALPARAMETERS_H_

#include <experimental/filesystem>

class GlobalParameters
{
protected:
	GlobalParameters() = default;
public:
	static std::experimental::filesystem::path Path;
};

#endif //_GLOBALPARAMETERS_H_