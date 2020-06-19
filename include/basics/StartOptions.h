#pragma once

#ifndef INC_STARTOPTIONS_H_
#define INC_STARTOPTIONS_H_

#include "BasicMacros.h"

#include <string>
#include <map>
#include <utility>
#include <regex>
#include <functional>

#include "Logger.h"

class IStartOptionDependeable
{
	MY_INTERFACE(IStartOptionDependeable)
private:
protected:
public:
	virtual void fromOption(std::smatch match) = 0;
	virtual std::string getOptionString() = 0;
	virtual std::regex getOptionRegex() = 0;
};

// Class StartOptions
// Class which is used to register Command Parameters 
class StartOptions
{
private:
	typedef void(*FuncOptNotFound)(void);
	typedef void(*FuncOptFound)(std::string);
	typedef std::tuple<std::string, FuncOptFound, FuncOptNotFound, std::string> OptInfo;
	typedef std::map<std::string, OptInfo> OptType;


	OptType moptions;
	std::map<std::string, std::string> FoundwithArgument;

	void registerOption(const std::string optionname, OptInfo Info);

protected:
public:

	StartOptions() {}
	virtual ~StartOptions() = default;

	// Register a Startoption 
	// the Optionregex must be formated in a way so that match is the optionflag  

	void registerOption(const std::string& optionname, const std::string& optionflag, const FuncOptFound& found, const FuncOptNotFound& notfound, const std::string& comment);
	void registerOption(const std::string& optionname, const std::string& optionflag, const FuncOptFound& found, const FuncOptNotFound& notfound);

	//Checks if a option is registered
	bool isOptionRegistered(const std::string& option);

	//Checks wether a startargument is an registered option
	bool isArgumentRegistered(const std::string& s1, std::smatch &match, std::string &optionname);

	//Method which analyzes the arguments for registered options
	void analyzeStartArguments(int argc, char** argv);

	std::map<std::string, std::pair<std::string, std::string>> getOptions();

	void printOptions();


};

#endif //_STARTOPTIONS_H_
