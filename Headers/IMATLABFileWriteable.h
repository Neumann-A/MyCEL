#pragma once

#include "BasicMacros.h"
#include "MATLABFileHandler.h"

//#define WRITEVALUEINTOMAT(x,section)

///-------------------------------------------------------------------------------------------------
/// <summary>	Interface Class: If Class inherits from this Class it can be written to MATLAB. </summary>
///
/// <remarks>	Alexander Neumann, 05.06.2016. </remarks>
///-------------------------------------------------------------------------------------------------
template<typename T>
class IMATLABFileWriteable
{
	MY_INTERFACE(IMATLABFileWriteable<T>)
private:	
protected:
public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Function which creates a Matlab Struct/Array. </summary>
	///
	/// <remarks>	Alexander Neumann, 05.06.2016. </remarks>
	///
	/// <returns>	The new matlab array. </returns>
	///-------------------------------------------------------------------------------------------------
	//CLASS_STATIC_AND_OBJ_FUNC(mxArray&,T,createMATLABarray,(),())
	virtual mxArray& createMATLABarray() const = 0;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Writes the contents of the class derived from this class into a Matlab File. </summary>
	///
	/// <remarks>	Alexander Neumann, 05.06.2016. </remarks>
	///
	/// <param name="File">   	[in,out] The MATLAB File Handler. </param>
	/// <param name="section">	The section name. </param>
	///-------------------------------------------------------------------------------------------------
	void WriteValuesToMATLABFile(MATLABFileHandler &File, const std::string &section) const
	{
		mxArray* data = this->createMATLABarray();
		File.insertArrayIntoMAT(*data, section);
	};

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Writes the contents of the class derived from this class into a Matlab mxArray. </summary>
	///
	/// <remarks>	Alexander Neumann, 05.06.2016. </remarks>
	///
	/// <param name="Struct"> 	[in,out] The MATLAB struct or array. </param>
	/// <param name="section">	The section name. </param>
	///-------------------------------------------------------------------------------------------------
	void WriteValuesToMATLABFile(mxArray &Struct, const std::string &section) const
	{
		mxArray& data = this->createMATLABarray();
		MATLABFileHandler::insertSingleElementIntoStruct(Struct, section, data);
	};
};