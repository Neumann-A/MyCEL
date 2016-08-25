#pragma once


#include <iostream>
#include <string>
#include <sstream> // Stringstream

#include <cstdarg>

class Logger
{
private:
	Logger() {};
	virtual ~Logger() {};

protected:
	
public:
	inline static void Log(const std::string &msg) 
	{ 
		std::cout << msg << std::endl;
	};
	inline static void Log(const std::stringstream &msg) 
	{ 
		std::cout << msg.str() << std::endl;
	};
	inline static void Log(const char* fmt, ...)
	{
#pragma warning( push )
#pragma warning( disable : 6386 )
		const size_t size = 512;
		char* buffer = nullptr;
		buffer = new char[size];
		va_list vl;
		va_start(vl, fmt);
		int nsize = vsnprintf(buffer, size, fmt, vl);
		if (size <= nsize)
		{	//fail delete buffer and try again
			delete[] buffer;
			buffer = nullptr;
			buffer = new char[static_cast<size_t>(nsize) + 1]; //+1 for /0
			nsize = vsnprintf(buffer, size, fmt, vl);
		}
		std::string ret{ buffer };
		va_end(vl);
		delete[] buffer;
		std::cout << ret << std::endl;
#pragma warning( pop )
	}

	inline static void Error(const std::string &msg)
	{
		std::cerr << msg << std::endl;
	};
	inline static void Error(const std::stringstream &msg)
	{
		std::cerr << msg.str() << std::endl;
	};
	inline static void Error(const char* fmt, ...)
	{
#pragma warning( push )
#pragma warning( disable : 6386 )
		const size_t size = 512;
		char* buffer = nullptr;
		buffer = new char[size];
		va_list vl;
		va_start(vl, fmt);
		int nsize = vsnprintf(buffer, size, fmt, vl);
		if (size <= nsize)
		{	//fail delete buffer and try again
			delete[] buffer;
			buffer = nullptr;
			buffer = new char[static_cast<size_t>(nsize) + 1]; //+1 for /0
			nsize = vsnprintf(buffer, size, fmt, vl);
		}
		std::string ret{ buffer };
		va_end(vl);
		delete[] buffer;
		std::cout << ret << std::endl;
#pragma warning( pop )
	}

	inline static std::string Format(const char* fmt, ...)
	{
#pragma warning( push )
#pragma warning( disable : 6386 )
		const size_t size = 512;
		char* buffer = 0;;
		buffer = new char[size];;
		va_list vl;;
		va_start(vl, fmt);;
		int nsize = vsnprintf(buffer, size, fmt, vl);;
		if (size <= nsize)
		{	//fail delete buffer and try again
			delete[] buffer;
			//buffer = 0;
			buffer = new char[static_cast<size_t>(nsize) + 1]; //+1 for /0
			nsize = vsnprintf(buffer, size, fmt, vl);
		}
		std::string ret{ buffer };
		va_end(vl);
		delete[] buffer;
		return ret;
#pragma warning( pop )
	}

};