#include "StartOptions.h"


void StartOptions::registerOption(const std::string optionname, OptInfo Info)
{
	// Do not allow to register the same option twice
	if (isOptionRegistered(optionname))
	{
		Logger::Error("Error on line %d in file %s: Option %s is already registered!", __LINE__, __FILE__, optionname.c_str());
		return;
	}

	_options[optionname] = Info;
}

void StartOptions::registerOption(const std::string& optionname, const std::string& optionflag, const FuncOptFound& found, const FuncOptNotFound& notfound, const std::string& comment)
{
	registerOption(optionname, OptInfo{ optionflag, found, notfound, comment });
}
void StartOptions::registerOption(const std::string& optionname, const std::string& optionflag, const FuncOptFound& found, const FuncOptNotFound& notfound)
{
	registerOption(optionname, optionflag, found, notfound, std::string{ " " });
}

//Checks if a option is registered
bool StartOptions::isOptionRegistered(const std::string option)
{
	return (_options.find(option) != _options.end());
};
//Checks wether a startargument is an registered option
bool StartOptions::isArgumentRegistered(std::string s1, std::smatch &match, std::string &optionname)
{
	bool found = false;

	for (const auto& it : _options)
	{
		std::regex rx{ std::get<0>(it.second) };
		found = std::regex_search(s1, match, rx);
		if (found)
		{
			Logger::Log("StartOptions: Found Option " + it.first + " with " + std::get<0>(it.second));
			optionname = it.first;
			break;
		}
	}
	return found;
};

//Method which analyzes the arguments for registered options
void StartOptions::analyzeStartArguments(int argc, char** argv)
{
	// First parse the Arguments and Fill _FoundwithArgument
	for (int i = 1; i < argc; ++i) // Ignores element 0;
	{
		std::smatch match;
		std::string optionname;
		if (isArgumentRegistered(std::string{ argv[i] }, match, optionname))
		{
			if (_FoundwithArgument.find(optionname) != _FoundwithArgument.end())
			{
				Logger::Error("Error on line %d in file %s: Argument %s was already found as an option!", __LINE__, __FILE__, argv[i]);
				return;
			}
			_FoundwithArgument[optionname] = match.suffix().str(); //push argument in found list
		}
		else
		{
			if (i != 0)
				Logger::Error("Error on line %d in file %s: Argument %s is not registered as an option!", __LINE__, __FILE__, argv[i]);
		}

	}

	//Second loop the options
	for (const auto& it : _options)
	{
		std::string option = it.first;
		auto FoundIt = _FoundwithArgument.find(option);

		if (FoundIt == _FoundwithArgument.end())
		{
			//Option was not found while parsing
			FuncOptNotFound func = (std::get<2>(it.second));
			if (func == nullptr)
			{
				continue;
			}
			func();
		}
		else
		{
			//Option was found
			FuncOptFound func = (std::get<1>(it.second));
			if (func == nullptr)
			{
				continue;
			}
			func(FoundIt->second);
		}
	}

};

std::map<std::string, std::pair<std::string, std::string>> StartOptions::getOptions()
{
	std::map<std::string, std::pair<std::string, std::string>> s1;

	for (const auto &it : _options)
	{
		s1[it.first] = std::pair<std::string, std::string>(std::get<0>(it.second), std::get<3>(it.second));
	}

	return s1;
}

void StartOptions::printOptions()
{
	Logger::Log("Valid command line parameters are: (without the)");
	Logger::Log("Flag : Name // Comment");

	for (const auto &i : _options)
	{
		Logger::Log(std::get<0>(i.second) + " : " + i.first + " // " + std::get<3>(i.second));
	}

}