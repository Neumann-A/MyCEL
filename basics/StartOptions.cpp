#include "StartOptions.h"


void StartOptions::registerOption(const std::string optionname, OptInfo Info)
{
	// Do not allow to register the same option twice
	if (isOptionRegistered(optionname))
	{
		Logger::Error("Error on line %d in file %s: Option %s is already registered!", __LINE__, __FILE__, optionname.c_str());
		return;
	}

	moptions[optionname] = Info;
}

void StartOptions::registerOption(const std::string& optionname, const std::string& optionflag, const FuncOptFound& found, const FuncOptNotFound& notfound, const std::string& comment)
{
	registerOption(optionname, OptInfo{ optionflag, found, notfound, comment });
}
void StartOptions::registerOption(const std::string& optionname, const std::string& optionflag, const FuncOptFound& found, const FuncOptNotFound& notfound)
{
	registerOption(optionname, optionflag, found, notfound, std::string{});
}

//Checks if a option is registered
bool StartOptions::isOptionRegistered(const std::string& option)
{
	return (moptions.find(option) != moptions.end());
};
//Checks wether a startargument is an registered option
bool StartOptions::isArgumentRegistered(const std::string& s1, std::smatch &match, std::string &optionname)
{
	bool found = false;

	for (const auto& it : moptions)
	{
		const auto& rxstr{ std::get<0>(it.second) };
		const std::regex rx{ rxstr };
		found = std::regex_search(s1, match, rx);
		if (found)
		{
			Logger::Log("StartOptions: Found Option " + it.first + " using " + rxstr + ".Parameter is:");
			optionname = it.first;
			break;
		}
	}
	return found;
};

//Method which analyzes the arguments for registered options
void StartOptions::analyzeStartArguments(int argc, char** argv)
{
	// First parse the Arguments and Fill FoundwithArgument
	for (int i = 1; i < argc; ++i) // Ignores element 0;
	{
		std::smatch match;
		std::string optionname;
		std::string str{ argv[i] };
		if (isArgumentRegistered(str, match, optionname))
		{
			if (FoundwithArgument.find(optionname) != FoundwithArgument.end())
			{
				Logger::Error("Error on line %d in file %s: Argument %s was already found as an option!", __LINE__, __FILE__, argv[i]);
				return;
			}
			const auto test = match[0].length();
			str.erase(0, test);
			std::swap(FoundwithArgument[optionname], str); //push argument in found list
		}
		else
		{
			if (i != 0)
				Logger::Error("Error on line %d in file %s: Argument %s is not registered as an option!", __LINE__, __FILE__, argv[i]);
		}

	}

	//Second loop the options
	for (const auto& elem : moptions)
	{
		const std::string option{ elem.first };
		const auto FoundIt = FoundwithArgument.find(option);

		if (FoundIt == FoundwithArgument.end())
		{ //Option was not found while parsing			
			FuncOptNotFound func = (std::get<2>(elem.second));
			if (func == nullptr) {
				continue;
			}
			func();
		}
		else
		{
			//Option was found
			FuncOptFound func = (std::get<1>(elem.second));
			if (func == nullptr) {
				continue;
			}
			func(FoundIt->second);
		}
	}

};

std::map<std::string, std::pair<std::string, std::string>> StartOptions::getOptions()
{
	std::map<std::string, std::pair<std::string, std::string>> s1;

	for (const auto &it : moptions)
	{
		s1[it.first] = std::pair<std::string, std::string>(std::get<0>(it.second), std::get<3>(it.second));
	}

	return s1;
}

void StartOptions::printOptions()
{
	Logger::Log("Valid command line parameters are: (without the)");
	Logger::Log("Flag : Name // Comment");

	for (const auto &i : moptions)
	{
		Logger::Log(std::get<0>(i.second) + " : " + i.first + " // " + std::get<3>(i.second));
	}

}