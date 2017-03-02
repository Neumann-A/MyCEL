#pragma once


#include <iostream>
#include <string>
#include <sstream> // Stringstream
#include <chrono>

#include <cstdarg>

class Logger
{
private:
	Logger() = default;
protected:
	
public:
	// In the near future when fold expressions are a thing
	//template<typename... Args>
	//inline static void Log(Args&&... args)
	//{
	//	std::stringstream str;
	//	str << ... << args ;
	//	Log(str);
	//}

	inline static void Log(const std::string &msg) 
	{ 
		//TODO: Implement Time as an extra
		std::cout << msg << std::endl;
	};
	inline static void Log(const std::stringstream &msg) 
	{ 
		Log(msg.str());
	};
	inline static void Log(const char* fmt, ...)
	{
#pragma warning( push )
#pragma warning( disable : 6386 )
		const int size = 512;
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
		Log(ret);
#pragma warning( pop )
	}

	inline static void Error(const std::string &msg)
	{
		std::cerr << msg << std::endl;
	};
	inline static void Error(const std::stringstream &msg)
	{
		Error(msg.str());
	};
	inline static void Error(const char* fmt, ...)
	{
#pragma warning( push )
#pragma warning( disable : 6386 )
		const int size = 512;
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
		Error(ret);
#pragma warning( pop )
	}

	inline static std::string Format(const char* fmt, ...)
	{
#pragma warning( push )
#pragma warning( disable : 6386 )
		const int size = 512;
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