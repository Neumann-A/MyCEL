#pragma once

#ifndef _CONFIGFILE_H_
#define _CONFIGFILE_H_

#include "Logger.h"
//#include "IConfigFile.h"
#include "BasicIncludes.h"

#include <filesystem>

#include <type_traits>
#include "Is_Container.h"

#include <map>

#include <iostream>
#include <fstream>

#include <sstream>
#include <string>

#include <regex>

#include <Eigen/Core>

//http://www.dreamincode.net/forums/topic/183191-create-a-simple-configuration-file-parser/
//http://www.informit.com/articles/article.aspx?p=2079020
//http://www.cplusplus.com/reference/regex/ECMAScript/

//std::string s1{ "[Test.map.help]" };
//std::string search_string{ "\\[[a-zA-Z]+(\\.?[a-zA-Z]+)+\\]" };
//std::regex rx{ search_string };
//auto found = std::regex_search(s1, rx);
//std::cout << "Teststring " << s1 << " gefunden: " << found << std::endl;
//std::sregex_iterator it{ s1.begin(), s1.end(), rx };
//std::sregex_iterator it_end;
//std::cout << (*it).str() << std::endl;

/*
abc… 	Letters
123… 	Digits
\d 	Any Digit
\D 	Any Non-digit character
. 	Any Character
\. 	Period
[abc] 	Only a, b, or c
[^abc] 	Not a, b, nor c
[a-z] 	Characters a to z
[0-9] 	Numbers 0 to 9
\w 	Any Alphanumeric character
\W 	Any Non-alphanumeric character
{m} 	m Repetitions
{m,n} 	m to n Repetitions
* 	Zero or more repetitions
+ 	One or more repetitions
? 	Optional character
\s 	Any Whitespace
\S 	Any Non-whitespace character
^…$ 	Starts and ends
(…) 	Capture Group
(a(bc)) 	Capture Sub-group
(.*) 	Capture all
(abc|def) 	Matches abc or def
*/

class ConfigFile
{
private:
	typedef std::map<std::string, std::string> keyvalues;
	typedef std::map<std::string, keyvalues> sections;
	
	sections _contents;	//Contents of the CFG
	std::tr2::sys::path _fName;	//Current Filename
	
	// Section String has the form: [parta.partb.partx] with an arbitary number of whitespace before or after. Section string does not contain numbers!
	static std::string section_string;// { "(?:^\\s*\\[)([a-zA-Z0-9_]+(\\.[a-zA-Z0-9_]+)*)(?:\\][:space:]*)$" };
	static std::regex section_regex; //= std::regex{section_string};// { section_string };

	// Keyvalue String has the form ( key    =   value wert      ). Whitespace before and after key or value will be automatically trimmed:
	static std::string keyvalue_string;// { "^(?:\\s*)([a-zA-Z0-9_]+)(?:\\s*)=(?:\\s*)(.*\\S)(?:\\s*)$" };
	static std::regex keyvalue_regex;// { keyvalue_string };
	
	// Comments
	static std::string comments_string;// { "\\s*((//)|(%)|(;)|(#))" };
	static std::regex comments_regex;// { comments_string };

	// Whitespaces only
	static std::string whites_string;// { "^\\s*$" };
	static std::regex whites_regex;// { comments_string };

	// Pair String
	static std::string pair_string;// {"^\\{(\\S+)((?:\\s*),(?:\\s*)(\\S+))+\\}$"};
	static std::regex pair_regex;// { pair_string };

	// String within Braces
	static std::string braces;// { "(?:\\{)(?:\\s*).*(?:\\s*)(?:\\})" };
	static std::regex braces_regex;// { braces, std::regex::nosubs };

	// Comma Seperator Regex
	static std::string comma;// { "," };
	static std::regex comma_regex;// { comma };

	// Removes commented Linies
	void removeComment(std::string &line) const;

	// Checks whether a line contains only whitespaces
	bool onlyWhitespace(const std::string &line) const;
	
	//Checks if a Line is a valid Key Value line (key = value)
	bool validKeyValueLine(const std::string &line, std::smatch &match) const;
	bool validKeyValueLine(const std::string &line) const;

	//Checks if a Line is a valid Section line ([Sectionparta.partb.partc.partd])
	bool validSectionLine(const std::string &line, std::smatch &match) const;
	bool validSectionLine(const std::string &line) const;

	// Extracts the Key and Value string from the found match
	void extractKeyValue(const std::smatch &match, std::string &key, std::string &value) const;

	// Returns the section string of the found section match
	std::string extractSection(const std::smatch &match) const;

	// lineNo = the current line number in the file.
	// line = the current line, with comments removed.
	void parseLine(const std::string &line, size_t const lineNo, std::string &currentSection);

	//loads contents from file
	void loadCFG(const std::tr2::sys::path& fName);

	//Writes contents to file
	void writeCFG(const std::tr2::sys::path& fName) const;
	

	// easy error logging
	void exitWithError(const std::string &error) const;

	// Tests if a key within a section exists
	bool keyExists(const std::string & section, const std::string & key, keyvalues::const_iterator &it) const;
	bool keyExists(const sections::const_iterator &section, const std::string & key, keyvalues::const_iterator &it) const;
	
	// Tests if a section exists
	bool sectionExists(const std::string & section, sections::const_iterator &it) const;

	static std::vector<std::string> extractBracedList(const std::string& key);
	
	template<typename T>
	static std::enable_if_t<stdext::is_container<T>::value && std::is_arithmetic<typename T::value_type>::value, std::string> createBracedList(const T& values)
	{
		std::stringstream sstr;
		sstr << "{";
		bool first = true;
		for (const auto& iter : values)
		{
			if (first)
			{
				sstr << BasicTools::toStringScientific<typename T::value_type>(iter);
				first = false;
			}
			else
			{
				sstr << ", " << BasicTools::toStringScientific<typename T::value_type>(iter);
			}

		}
		sstr << "}";
		return sstr.str();
	}

	template<typename T>
	static std::enable_if_t<stdext::is_container<T>::value && std::is_same<typename T::value_type, std::string>::value, std::string> createBracedList(const T& values)
	{
		std::stringstream sstr;
		sstr << "{";
		bool first = true;
		for (const auto& iter : values)
		{
			if (first)
			{
				sstr << iter;
				first = false;
			}
			else
			{
				sstr << ", " << iter;
			}

		}
		sstr << "}";
		return sstr.str();
	}

protected:
public:
	ConfigFile() {};
	ConfigFile(const std::string& fName);
	ConfigFile(const std::tr2::sys::path& fName);

	std::tr2::sys::path getConfigFilePath() const;

	// adds or overwrites a Key Value pair in a specific section
	void addKeyValue(std::string section, std::string key, std::string value);
	
	std::vector<std::string> getAllKeysInSection(const std::string& section) const;

	template <typename T>
	std::enable_if_t<std::is_arithmetic<T>::value && !std::is_same<std::remove_all_extents_t<T>,bool>::value, void> 
	addKeyValue(std::string section, std::string key, const T& value)
	{
		addKeyValue(section, key, BasicTools::toStringScientific<std::remove_all_extents_t<T>>(value));
	}

	template <typename T>
	std::enable_if_t<std::is_arithmetic<T>::value && std::is_same<std::remove_all_extents_t<T>, bool>::value, void>
		addKeyValue(std::string section, std::string key, const T& value)
	{
		std::string boolstr = value ? "TRUE" : "FALSE";
		addKeyValue(section, key, boolstr);
	}

	template <typename T1, typename T2>
	std::enable_if_t<std::is_arithmetic<T1>::value&&std::is_arithmetic<T2>::value, void>
		addKeyValue(const std::string& section,const std::string& key, const std::pair<T1,T2> &values)
	{
		std::pair < T1, T2 > tmp{values};
		std::stringstream sstr;
		sstr << "{" << BasicTools::toStringScientific<T1>(tmp.first) << "," << BasicTools::toStringScientific<T2>(tmp.second) << "}";
		addKeyValue(section, key, sstr.str());		
		tmp = std::pair < T1, T2 >{ 1,1 };
	}

	template <typename T>
	std::enable_if_t<std::is_same<T, std::vector<typename T::value_type, typename T::allocator_type>>::value && std::is_arithmetic<typename T::value_type>::value, void>
		addKeyValue(const std::string& section, const std::string& key, const T &values)
	{
		addKeyValue(section, key, createBracedList(values));
	}


	template <typename T>
	std::enable_if_t<std::is_same<T,std::vector<std::string>>::value, void>
		addKeyValue(const std::string& section, const std::string& key, const T &values)
	{
		addKeyValue(section, key, createBracedList(values));
	}

	template <typename T>
	std::enable_if_t<std::is_floating_point<typename T::Scalar>::value, void>  addKeyValue(const std::string& section, const std::string& key, const T &values)
	{
		Eigen::IOFormat CommaInitFmt(Eigen::FullPrecision, Eigen::DontAlignCols, ", ", ", ", "", "", "{", "}");
		std::stringstream sstr;
		sstr << std::scientific << values.format(CommaInitFmt);
		addKeyValue(section, key, sstr.str());
	}

	// Clears the content of the cfg object
	void clearAll() _NOEXCEPT;
	// Writes content of teh CFG object into the file
	void writeToFile(const std::tr2::sys::path &filename);
	//void writeToMatlab(const std::string &filename) {};
	//Get the stringvalue the key within section has
	std::string getValueOfKeyInSection(const std::string &section, const std::string &key) const;

	bool getBooleanOfKeyInSection(const std::string &section, const std::string &key) const;

	template <typename T>
	std::enable_if_t<std::is_arithmetic<T>::value,T> getNumericValueOfKeyInSection(const std::string &section, const std::string &key) const
	{
		size_t pos = 0;
		std::string stringtoconvert = getValueOfKeyInSection(section,key);

		if (stringtoconvert.empty())
		{
			Logger::Error("ConfigFile: Empty String conversion to numeric. Section: "+section+ " ,Key: "+ key);
			return 0;
		}
		T value = BasicTools::stringToNumber<T>(stringtoconvert, pos);

		if (!(pos >= stringtoconvert.size()))
			Logger::Log("CFG: Numeric Conversion failed. Section: " + section + " Key: " + key + " String: " + stringtoconvert);
		
		return value;
	}

	template<typename T1, typename T2>
	std::enable_if_t<std::is_arithmetic<T1>::value&&std::is_arithmetic<T2>::value,std::pair<T1, T2>>
		getNumericPairValueOfKeyInSection(const std::string &section, const std::string &key) const
	{
		size_t pos = 0;
		std::string stringtoconvert = getValueOfKeyInSection(section, key);
		if (stringtoconvert.empty())
		{
			Logger::Error("ConfigFile: Empty String conversion to numeric. Section: " + section + " ,Key: " + key);
			return std::pair<T1, T2>{};
		}

		std::vector<std::string> values = extractBracedList(stringtoconvert);
		

		if (values.size()!=2)
		{
			Logger::Error("ConfigFile: Braced values do not represent a pair. Section: " + section + " ,Key: " + key);
			return std::pair<T1, T2>{};
		}

		std::string tmp{ values.at(0) };
		T1 val1 = BasicTools::stringToNumber<T1>(tmp, pos);

		if (!(pos >= tmp.size()))
			Logger::Log("CFG: Numeric Conversion failed. Section: " + section + " Key: " + key + " String: " + tmp);

		tmp = values.at(1);
		T2 val2 = BasicTools::stringToNumber<T2>(values.at(1), pos);

		if (!(pos >= tmp.size()))
			Logger::Log("CFG: Numeric Conversion failed. Section: " + section + " Key: " + key + " String: " + tmp);

		std::pair<T1, T2> pair{ val1,val2 };
		return pair;

	};

	template<typename T>
	std::enable_if_t<stdext::is_stl_container<T>::value && std::is_arithmetic<typename T::value_type>::value, T>
		getNumericValuesOfKeyInSection(const std::string &section, const std::string &key) const
	{
		size_t pos = 0;
		std::string stringtoconvert = getValueOfKeyInSection(section, key);
		if (stringtoconvert.empty())
		{
			Logger::Error("ConfigFile: Empty String conversion to numeric. Section: " + section + " ,Key: " + key);
			return T{};
		}

		std::vector<std::string> values = extractBracedList(stringtoconvert);
		T result;
		for (const auto& iter : values)
		{
			result.push_back(BasicTools::stringToNumber<typename T::value_type>(iter, pos));
			if (!(pos >= iter.size()))
				Logger::Log("CFG: Numeric Conversion failed. Section: " + section + " Key: " + key + " String: " + iter);
		}
		return result;

	}

	static bool removeBraces(std::string& str);

	//For debugging 
	void writeContentsToConsole() const;
};

#endif //_CONFIGFILE_H_