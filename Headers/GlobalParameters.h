#pragma once

#ifndef _GLOBALPARAMETERS_H_
#define _GLOBALPARAMETERS_H_

#include <string>

class GlobalParameters
{
protected:
	GlobalParameters() {};
public:
	virtual ~GlobalParameters() {};
	
	static std::string Path;
};

#endif //_GLOBALPARAMETERS_H_