

#include "ConfigFile.h"

std::string ConfigFile::section_string { "(?:^\\s*\\[)([a-zA-Z0-9_]+(\\.[a-zA-Z0-9_]+)*)(?:\\][:space:]*)$" };
std::regex ConfigFile::section_regex{section_string};

// Keyvalue String has the form ( key    =   value wert      ). Whitespace before and after key or value will be automatically trimmed:
std::string ConfigFile::keyvalue_string { "^(?:\\s*)([a-zA-Z0-9_]+)(?:\\s*)=(?:\\s*)(.*\\S)(?:\\s*)$" };
std::regex ConfigFile::keyvalue_regex { keyvalue_string };

// Comments
std::string ConfigFile::comments_string { "\\s*((//)|(%)|(;)|(#))" };
std::regex ConfigFile::comments_regex { comments_string };

// Whitespaces only
std::string ConfigFile::whites_string { "^\\s*$" };
std::regex ConfigFile::whites_regex{ comments_string };

// Pair String
std::string ConfigFile::pair_string {"^\\{(\\S+)((?:\\s*),(?:\\s*)(\\S+))+\\}$"};
std::regex ConfigFile::pair_regex { pair_string };

// String within Braces
std::string ConfigFile::braces { "(?:\\{)(?:\\s*).*(?:\\s*)(?:\\})" };
std::regex ConfigFile::braces_regex { braces, std::regex::nosubs };

// Comma Seperator Regex
std::string ConfigFile::comma { "," };
std::regex ConfigFile::comma_regex { comma };

std::tr2::sys::path ConfigFile::getConfigFilePath() const
{
	std::tr2::sys::path path{ _fName };
	return path.remove_filename();
	//const size_t last_slash_idx = _fName.find_last_of('\\/');
	//if (std::string::npos != last_slash_idx)
	//{
	//	directory = _fName.substr(0, last_slash_idx);
	//}
	//return directory;
};

ConfigFile::ConfigFile(const std::string &fName) : _fName(fName)
{
	loadCFG(_fName);
};

ConfigFile::ConfigFile(const std::tr2::sys::path &fName) : _fName(fName)
{
	loadCFG(_fName);
};

std::vector<std::string> ConfigFile::getAllKeysInSection(const std::string& section) const
{
	sections::const_iterator secit;
	if (!sectionExists(section, secit))
	{
		Logger::Log("CFG: Section not found! Section:" + section);
		return std::vector<std::string>{};
	}
	
	std::vector < std::string > res;
	for (const auto& key : secit->second)
	{
		res.push_back(key.first);
	}
	return res;
};


void ConfigFile::clearAll() _NOEXCEPT
{
	_contents.clear();
}

void ConfigFile::writeToFile(const std::tr2::sys::path &filename)
{
	_fName = filename;
	writeCFG(filename);
}

void ConfigFile::writeContentsToConsole() const
{
	if (_contents.empty())
		std::cout << "Nothing to write to console" << std::endl;

	for (auto sections : _contents)
	{
		std::cout << "[" << sections.first << "]" << std::endl;
		for (auto keys : sections.second)
		{
			std::cout << keys.first << " = " << keys.second << std::endl;
		}
		std::cout << "[EOS]" << std::endl << std::endl;
	}
};

void ConfigFile::removeComment(std::string &line) const
{
	std::smatch match;
	if (std::regex_search(line, match, comments_regex))
	{
		line.erase(match.position());
		//Logger::Log("Comment found and removed");
	}
}

bool ConfigFile::onlyWhitespace(const std::string &line) const
{
	return (std::regex_search(line, whites_regex) || line.empty());
}

bool ConfigFile::validKeyValueLine(const std::string &line, std::smatch &match) const
{
	return (std::regex_match(line, match, keyvalue_regex));
}
bool ConfigFile::validKeyValueLine(const std::string &line) const
{
	return (std::regex_match(line, keyvalue_regex));
}
bool ConfigFile::validSectionLine(const std::string &line, std::smatch &match) const
{
	return (std::regex_match(line, match, section_regex));
}
bool ConfigFile::validSectionLine(const std::string &line) const
{
	return (std::regex_match(line, section_regex));
}

void ConfigFile::extractKeyValue(const std::smatch &match , std::string &key, std::string &value) const
{
	key = match.str(1);
	value = match.str(2);
}

std::string ConfigFile::extractSection(const std::smatch &match) const
{
	return match.str(1);
}

void ConfigFile::addKeyValue(std::string section, std::string key, std::string value)
{
	std::string s{ " " + key + " = " + value };
	if (!validKeyValueLine(s))
	{
		Logger::Log("Key and\\or Value does not fullfill requirements for CFG");
		return;
	}
	if (!validSectionLine("["+section+"]"))
	{
		Logger::Log("Section does not fullfill requirements for CFG");
		return;
	}
	_contents[section][key] = value;
}

bool ConfigFile::keyExists(const std::string & section, const std::string & key, keyvalues::const_iterator &it) const
{
	auto its = _contents.find(section);
	if (its == _contents.end())
		return false;

	it = its->second.find(key);
	return (it != its->second.end());
}
bool ConfigFile::keyExists(const sections::const_iterator &section, const std::string & key, keyvalues::const_iterator &it) const
{
	it = section->second.find(key);
	return (it != section->second.end());
}

bool ConfigFile::sectionExists(const std::string & section, sections::const_iterator &it) const
{
	it = _contents.find(section);
	return (it != _contents.end());
}

void ConfigFile::parseLine(const std::string &line, size_t const lineNo, std::string &currentSection)
{
	// Comments and Whitespace lines are alread ignored / removed
	// So we should only have either a valid section line or a valid keyvalue line
	std::smatch match;

	if (validKeyValueLine(line, match))
	{
		std::string key, value;
		extractKeyValue(match, key, value);
		_contents[currentSection][key] = value;
		return;
	}

	if (validSectionLine(line, match))
	{
		currentSection = extractSection(match);
		return;
	}

	exitWithError("CFG: Line Number: " + std::to_string(lineNo) + " is not valid. Line is: " + line + "\n");
}

void ConfigFile::loadCFG(const std::tr2::sys::path& fName)
{
	std::ifstream file;
	file.open(fName, std::ios::in);
	if (!file)
	{
		exitWithError("CFG: File " + _fName.string() + " couldn't be found!\n");
		return;
	}

	std::string line;
	std::string currentSection;

	size_t lineNo = 0;
	bool FirstRun = true;

	while (std::getline(file, line))
	{
		++lineNo;

		std::string temp{ line };

		if (temp.empty())
			continue;

		removeComment(temp);
		if (onlyWhitespace(temp))
			continue;

		if (FirstRun)
		{
			std::smatch match;
			if (validSectionLine(temp, match))
				currentSection = extractSection(match);
			else
			{
				exitWithError("CFG Parse Error: First non comment\\whitespace line is not a section header!");
				break;
			}
			FirstRun = false;
		}
		else
			parseLine(temp, lineNo, currentSection);
	}

	file.close();
}

void ConfigFile::writeCFG(const std::tr2::sys::path& fName) const
{
	std::ofstream file;
	file.open(fName, std::ios::out);
	if (!file)
	{
		exitWithError("CFG: File " + _fName.string() + " couldn't be found!\n");
		return;
	}

	if (_contents.empty()) // Nothing to write
	{
		exitWithError("CFG: Nothing to write into file");
		return;
	}

	for (auto sections : _contents)
	{
		file << "[" << sections.first << "]" << std::endl;
		for (auto keys : sections.second)
		{
			file << keys.first << " = " << keys.second << std::endl;
		}
		file << std::endl;
	}
	file.close();
};

void ConfigFile::exitWithError(const std::string &error) const
{
	Logger::Log(error);
}

std::string ConfigFile::getValueOfKeyInSection(const std::string &section, const std::string &key) const
{
	sections::const_iterator secit;
	keyvalues::const_iterator keyit;
	if (!sectionExists(section, secit))
	{
		Logger::Log("CFG: Section not found! Section:" + section + ", Key: " + key);
		return std::string{};
	}
	if (!keyExists(secit, key, keyit))
	{
		Logger::Log("CFG: Key " + key + " within Section: " + secit->first + " not found");
		return std::string{};
	}
	return keyit->second;
}

bool ConfigFile::getBooleanOfKeyInSection(const std::string &section, const std::string &key) const
{
	std::string boolstr = getValueOfKeyInSection(section, key);
	std::regex rx{ "^[Tt][Rr][Uu][Ee]$" };
	return std::regex_search(boolstr, rx);
}

std::vector<std::string> ConfigFile::extractBracedList(const std::string& key) 
{
	
	std::string str{ key };
	std::vector<std::string> result;

	std::smatch match;
	if(removeBraces(str))
	{
		while (std::regex_search(str, match, comma_regex))
		{
			result.push_back(str.substr(0, match.position()));
			str.erase(0, match.position() + 1);
			//std::cout << "String after comma removal: " << str << std::endl;
		};
		result.push_back(str);
	}

	return result;
}
bool ConfigFile::removeBraces(std::string& str)
{
	std::smatch match;
	bool found = std::regex_search(str, match, braces_regex);
	if(found)
	{
		str.erase(match.length() - 1, str.length()); //remove Back Brace
		str.erase(0, match.position() + 1); //remove front Brace
	}
	return found;
};

//Template Instantiziations:
template void ConfigFile::addKeyValue<>(std::string, std::string, const bool&);
template void ConfigFile::addKeyValue<>(std::string, std::string, const float&);
template void ConfigFile::addKeyValue<>(std::string, std::string, const double&);
template void ConfigFile::addKeyValue<>(std::string, std::string, const long double&);
template void ConfigFile::addKeyValue<>(std::string, std::string, const int&);
template void ConfigFile::addKeyValue<>(std::string, std::string, const long&);
template void ConfigFile::addKeyValue<>(std::string, std::string, const long long&);
template void ConfigFile::addKeyValue<>(std::string, std::string, const unsigned long&);
template void ConfigFile::addKeyValue<>(std::string, std::string, const unsigned long long&);

#define TEMPLATEINSTANTFORNUMERIC(DefineMakro) \
 DefineMakro(float) \
 DefineMakro(double) \
 DefineMakro(long double) \
 DefineMakro(int) \
 DefineMakro(long) \
 DefineMakro(long long) \
 DefineMakro(unsigned int) \
 DefineMakro(unsigned long) \
 DefineMakro(unsigned long long) 

#define TEMPLATEINSTANTFORNUMERICRECURSIVE(Makro1,Makro2) \
	Makro1(float, Makro2) \
	Makro1(double, Makro2) \
	Makro1(long double, Makro2) \
	Makro1(int, Makro2) \
	Makro1(long, Makro2) \
	Makro1(long long, Makro2) \
	Makro1(unsigned int, Makro2) \
	Makro1(unsigned long, Makro2) \
	Makro1(unsigned long long, Makro2)

#define HELPER(Datatype) template Datatype ConfigFile::getNumericValueOfKeyInSection< Datatype > (const std::string&, const std::string&) const;
TEMPLATEINSTANTFORNUMERIC(HELPER)
#undef HELPER

//#define HELPER(Datatype) template std::vector< Datatype > ConfigFile::getNumericValuesOfKeyInSection< std::vector < Datatype > > (const std::string&, const std::string&) const;
//TEMPLATEINSTANTFORNUMERIC(HELPER)
//#undef HELPER

#define HELPER(Datatype) template std::pair< Datatype , Datatype > ConfigFile::getNumericPairValueOfKeyInSection< Datatype , Datatype >(const std::string&, const std::string&) const;
TEMPLATEINSTANTFORNUMERIC(HELPER)
#undef HELPER


//#define HELPER(Datatype) template std::vector< Datatype > ConfigFile::getNumericValuesOfKeyInSection< std::vector < Datatype > >(const std::string&, const std::string&) const;
//TEMPLATEINSTANTFORNUMERIC(HELPER)
//#undef HELPER

//#define HELPER(Datatype1,Datatype2) template std::pair< Datatype1 , Datatype2 > ConfigFile::getNumericPairValueOfKeyInSection< Datatype1 , Datatype2 >(const std::string&, const std::string&) const;
//TEMPLATEINSTANTFORNUMERICRECURSIVE(HELPER)
//#undef HELPER

//template float ConfigFile::getNumericValueOfKeyInSection<float>(const std::string&, const std::string&) const;
//template double ConfigFile::getNumericValueOfKeyInSection<double>(const std::string&, const std::string&) const;
//template long double ConfigFile::getNumericValueOfKeyInSection<long double>(const std::string&, const std::string&) const;
//template int ConfigFile::getNumericValueOfKeyInSection<int>(const std::string&, const std::string&) const;
//template long ConfigFile::getNumericValueOfKeyInSection<long>(const std::string&, const std::string&) const;
//template long long ConfigFile::getNumericValueOfKeyInSection<long long>(const std::string&, const std::string&) const;
//template unsigned long ConfigFile::getNumericValueOfKeyInSection<unsigned long>(const std::string&, const std::string&) const;
//template unsigned long long ConfigFile::getNumericValueOfKeyInSection<unsigned long long>(const std::string&, const std::string&) const;

//template std::pair<double,double> ConfigFile::getNumericPairValueOfKeyInSection<double,double>(const std::string&, const std::string&) const;