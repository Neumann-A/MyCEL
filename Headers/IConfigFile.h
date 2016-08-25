///---------------------------------------------------------------------------------------------------
// file:	Headers\IConfigFile.h
//
// summary: 	Declares the IConfigFile interface
//
//			Copyright (c) 2016 Alexander Neumann.
//
// author: Alexander Neumann
// date: 05.06.2016

#ifndef INC_IConfigFile_H
#define INC_IConfigFile_H
///---------------------------------------------------------------------------------------------------
#pragma once

#include "BasicMacros.h"
#include "ConfigFile.h"
#include <string>

//class ConfigFile; // Forward Declare ConfigFile

#define VARKEYVALUE(x) #x << "=" << x

#define WRITEVALUETOCONFIG(file,section,x) file.addKeyValue(section,std::string{VARNAME(x)},x);
//#define READVALUEFROMCONFIG(file,section,key) file.addKeyValue(section,std::string{VARNAME(x)},x);

///-------------------------------------------------------------------------------------------------
/// <summary>	Interface class for Config File General Information </summary>
///
/// <typeparam name="T">	Generic class with uses this Interface. </typeparam>
///-------------------------------------------------------------------------------------------------
template <typename T>
class IConfigFileGeneralInfo
{
	MY_INTERFACE(IConfigFileGeneralInfo<T>)
private:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Returns a string containing the config file section name for the class T </summary>
	///
	/// <returns> string containing an appropiate section name for the class T </returns>
	///-------------------------------------------------------------------------------------------------
	CLASS_STATIC_AND_OBJ_FUNC(std::string,T,getSectionName,(),());
protected:
public:	
};

/// <summary>	Interface which defines that the derived class can be written to a Config File </summary>
class IConfigFileWriteable 
{	
	MY_INTERFACE(IConfigFileWriteable)
private:
protected:
public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Writes the values to a configuration file. </summary>
	///
	/// <param name="File">	[in,out] The Config file. </param>
	///-------------------------------------------------------------------------------------------------
	virtual void WriteValuesToConfigFile(ConfigFile &File) const = 0;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Writes the values to a configuration file. </summary>
	///
	/// <param name="File">   	[in,out] The config file. </param>
	/// <param name="section">	The section to be used within the config file. </param>
	///-------------------------------------------------------------------------------------------------
	virtual void WriteValuesToConfigFile(ConfigFile &File, const std::string &section) const = 0;
	
};

/// <summary>	Interface for a Config file readable object </summary>
class IConfigFileReadable
{
	MY_INTERFACE(IConfigFileReadable)
private:
protected:
public:	

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets the values from configuration file. </summary>
	///
	/// <param name="File">	The config file. </param>
	///-------------------------------------------------------------------------------------------------
	virtual void GetValuesFromConfigFile(const ConfigFile &File) = 0;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets values from configuration file. </summary>
	///
	/// <param name="File">   	The config file. </param>
	/// <param name="section">	The section name to read from within the config file. </param>
	///-------------------------------------------------------------------------------------------------
	virtual void GetValuesFromConfigFile(const ConfigFile &File, const std::string &section) = 0;
};

///-------------------------------------------------------------------------------------------------
/// <summary>	Interface which defines that the object can be created from a config file </summary>
///
/// <typeparam name="T">	Generic class which should be creatable from the config file </typeparam>
///-------------------------------------------------------------------------------------------------
template <typename T>
class IConfigFileCreateable
{
	MY_INTERFACE(IConfigFileCreateable<T>)
private:

	///-------------------------------------------------------------------------------------------------
	/// <summary> Creates a Instance of Class T from the given config file </summary>
	/// 
	/// <param name="File">   	The config file. </param>
	/// <param name="section">	The section name to read from within the config file. </param>
	/// 
	/// <returns> Returns a valid object T </returns>
	///-------------------------------------------------------------------------------------------------
	CLASS_STATIC_AND_OBJ_FUNC(T, T, createObjectFromConfigFile, (const ConfigFile &file, const std::string &section), (file, section));
protected:
public:
};

template <typename T>
class IConfigFileCreateablePolymorph
{
	MY_VIRTUAL_INTERFACE(IConfigFileCreateablePolymorph<T>)
private:

	///-------------------------------------------------------------------------------------------------
	/// <summary> Creates a Instance of Class T from the given config file </summary>
	/// 
	/// <param name="File">   	The config file. </param>
	/// <param name="section">	The section name to read from within the config file. </param>
	/// 
	/// <returns> Returns a valid object T </returns>
	///-------------------------------------------------------------------------------------------------
	CLASS_STATIC_AND_OBJ_FUNC(std::unique_ptr<T>, T, createObjectFromConfigFile, (const ConfigFile &file, const std::string &section), (file, section));
protected:
public:
};

///-------------------------------------------------------------------------------------------------
/// <summary>	Interface which combines all config file interfaces </summary>
///
/// <seealso cref="T:IConfigFileWriteable"/>
/// <seealso cref="T:IConfigFileReadable"/>
/// <seealso cref="T:IConfigFileGeneralInfo{T}"/>
/// <seealso cref="T:IConfigFileCreateable{T}"/>
///-------------------------------------------------------------------------------------------------
template<typename T>
class IConfigFileAll : public IConfigFileWriteable, public IConfigFileReadable, public IConfigFileGeneralInfo<T>, public IConfigFileCreateable<T>
{
	MY_INTERFACE(IConfigFileAll)
private:
protected:
public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Writes values to a configuration file. </summary>
	///
	/// <param name="File">	[in,out] The config file. </param>
	///-------------------------------------------------------------------------------------------------
	void WriteValuesToConfigFile(ConfigFile &File) const override final
	{
		(static_cast<const T*>(this))->WriteValuesToConfigFile(File, T::getSectionName());
	};

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets values from a configuration file. </summary>
	///
	/// <param name="File">	The config file. </param>
	///-------------------------------------------------------------------------------------------------
	void GetValuesFromConfigFile(const ConfigFile &File) override final
	{
		GetValuesFromConfigFile(File, T::getSectionName());
	};

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets values from a configuration file. </summary>
	///
	/// <param name="File">   	The config file. </param>
	/// <param name="section">	The section to read from. </param>
	///-------------------------------------------------------------------------------------------------
	void GetValuesFromConfigFile(const ConfigFile &File, const std::string &section) override final
	{
		//std::swap(*(static_cast<T*>(this)), (T::createObjectFromConfigFile(File, section)));
		*(static_cast<T*>(this)) = T::createObjectFromConfigFile(File, section);
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Creates object from a configuration file. </summary>
	///
	/// <param name="file">	The config file. </param>
	///
	/// <returns>	The new object from configuration file. </returns>
	///-------------------------------------------------------------------------------------------------
	static T createObjectFromConfigFile(const ConfigFile &file)
	{
		return T::createObjectFromConfigFile(file, T::getSectionName());
	}
};

template<typename T>
class IConfigFileAllPolymorph : public IConfigFileWriteable, public IConfigFileReadable, public IConfigFileGeneralInfo<T>, public IConfigFileCreateablePolymorph<T>
{
	MY_VIRTUAL_INTERFACE(IConfigFileAllPolymorph)
private:
protected:
public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Writes values to a configuration file. </summary>
	///
	/// <param name="File">	[in,out] The config file. </param>
	///-------------------------------------------------------------------------------------------------
	void WriteValuesToConfigFile(ConfigFile &File) const override final
	{
		(static_cast<const T*>(this))->WriteValuesToConfigFile(File, T::getSectionName());
	};

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets values from a configuration file. </summary>
	///
	/// <param name="File">	The config file. </param>
	///-------------------------------------------------------------------------------------------------
	void GetValuesFromConfigFile(const ConfigFile &File) override final
	{
		GetValuesFromConfigFile(File, T::getSectionName());
	};

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets values from a configuration file. </summary>
	///
	/// <param name="File">   	The config file. </param>
	/// <param name="section">	The section to read from. </param>
	///-------------------------------------------------------------------------------------------------
	void GetValuesFromConfigFile(const ConfigFile &File, const std::string &section) override final
	{
		//std::swap(*(static_cast<T*>(this)), (T::createObjectFromConfigFile(File, section)));
		//*(static_cast<T*>(this)) = *((T::createObjectFromConfigFile(File, section))->get());
		*(static_cast<T*>(this)) = *T::createObjectFromConfigFile(File, section);
	}

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Creates object from a configuration file. </summary>
	///
	/// <param name="file">	The config file. </param>
	///
	/// <returns>	The new object from configuration file. </returns>
	///-------------------------------------------------------------------------------------------------
	static std::unique_ptr<T> createObjectFromConfigFile(const ConfigFile &file)
	{
		return T::createObjectFromConfigFile(file, T::getSectionName());
	}
};

#endif	// INC_IConfigFile_H
// end of Headers\IConfigFile.h
///---------------------------------------------------------------------------------------------------
