#pragma once
#include <string>
#include <regex>
#include <algorithm>
#include "Logger.h"
#include <atomic>

#include <vector>
#include <array>
#include <map>
#include <complex>

// Eigen Includes
#include <Eigen/Core>
#include <Eigen/StdVector>		// for Eigen std::vector allocator

//#include <engine.h> //To connect to matlab engine (we dont work directly with matlab so does not matter)
//MATLAB includes
#include <mat.h>
#pragma comment (lib, "libmx.lib")
#pragma comment (lib, "libeng.lib")
#pragma comment (lib, "libmex.lib")
#pragma comment (lib, "libmat.lib")
//Needs the following PATH = D:\Program Files\Matlab\R2015b\bin\win64; %PATH%

#include "MATLABClassFinder.h"

class MATLABFileHandler
{
private:
	std::atomic<bool> _isOpen{ false };
	MATFile * _pMat = nullptr; // Pointer to Matfile
	std::string _filename;

	/// Checks if the file was open
	inline bool checkOpen(const int &lineno) const
	{
		return (checkMatPointer(lineno));
	}

	/// checks wether the mat file is already open
	inline bool checkAlreadyOpen() 
	{
		if (_isOpen.exchange(true))
		{
			Logger::Error("MATLABFileHandler: Handler already opened a File!");
			return true;
		}
		return false;
	};

	/// Checks if the mat pointer is valid (not nullptr)
	inline bool checkMatPointer(const int &lineno) const
	{
		if (_pMat == nullptr)
		{
			Logger::Error("MATLABFileHandler: Pointer to MATFile not valid. Line: " + std::to_string(lineno));
			return false;
		}
		return true;
	}

	//Checks if the array Pointer is valid (not nullptr)
	inline static bool checkArrayPointer(mxArray *pArr,const int &lineno)
	{
		if (pArr == nullptr)
		{
			Logger::Error("MATLABFileHandler: Pointer to mxArray not valid on Line: "+ std::to_string(lineno));
			return false;
		}
		return true;
	}


	template<typename DataType, typename = typename std::enable_if<std::is_arithmetic<DataType>::value, DataType>::type>
	void addSingleValueToStruct(mxArray &pStruct, const std::string fieldname, const DataType &value)
	{
		//Fill Single Elements of Struct
		mxArray *valarray;
		valarray = mxCreateNumericMatrix(1, 1, MATLABClassFinder<DataType>::value, mxREAL);
		if (!checkArrayPointer(valarray, __LINE__))
			return;

		double * dataposition = mxGetPr(valarray);
		dataposition[0] = value;
		mxSetField(&pStruct, 0, fieldname.c_str(), valarray);
	}
protected:

	//	matOpen to open the file
	//	matGetVariable to get the cell array variable
	//	mxGetCell to get the pointer to the cell contents
	//	mxGetPr to get the pointer to the actual data
public:
	MATLABFileHandler() {};

	///Opens a Mat File for reading! (Read only!)
	void openMat(const std::string filename);
	
	///Creates a new Mat File (overwrites existing ones!); (Write Only!)
	void createMat(const std::string filename);
	
	///Opens or creates a MAT-File for writing and reading
	void updateOrCreateMat(const std::string filename);

	/// Creates a new Matlab Struct/Array
	static mxArray& createMATLABStruct();

	///Close Mat File
	void closeMat();

	template <typename DataType, typename = typename std::enable_if_t<std::is_arithmetic<DataType>::value, DataType>>
	static mxArray& createMATLABArray(const mwSize Cols,const mwSize Rows)
	{
		mxArray *valarray;
		valarray = mxCreateNumericMatrix(Cols, Rows, MATLABClassFinder<DataType>::value, mxREAL);
		return valarray;
	};

	template<typename DataType, typename std::enable_if_t<std::is_floating_point<DataType>::value, DataType> >  
	static mxArray& createMATLABArrayComplex(const mwSize Cols, const mwSize Rows)
	{
		mxArray *valarray;
		valarray = mxCreateNumericMatrix(Cols, Rows, MATLABClassFinder<DataType>::value, mxCOMPLEX);
		return valarray;
	};

	inline mxArray* getVariable(const std::string varname) 
	{
		return matGetVariable(_pMat, varname.c_str());
	}

	inline matError removeVariable(const std::string varname)
	{
		return matDeleteVariable(_pMat, varname.c_str());
	}

	//TODO create overload for complex type
	template<typename DataType, typename std::enable_if_t<std::is_arithmetic<DataType>::value, DataType*> = nullptr> //Numeric Types
	static void insertSingleElementIntoStruct(mxArray &Struct, const std::string &ElementName,const DataType &Value)
	{
		int index = mxAddField(&Struct, ElementName.c_str());

		if (index == -1)
			Logger::Error("MATLABFileHandler: Could not add Field to struct! (Out of Memory?)");

		mxArray *valarray;
		valarray = mxCreateNumericMatrix(1, 1, MATLABClassFinder<DataType>::value, mxREAL);
		if (!checkArrayPointer(valarray, __LINE__))
			return;
		*static_cast<DataType*>(mxGetData(valarray)) = Value;

		
		mxSetFieldByNumber(&Struct,0, index, valarray);
	}

	static void insertSingleElementIntoStruct(mxArray &Struct, const std::string &ElementName, const std::string &Value)
	{
		int index = mxAddField(&Struct, ElementName.c_str());

		if (index == -1)
			Logger::Error("MATLABFileHandler: Could not add Field to struct! (Out of Memory?)");

		mxArray *valarray;
		valarray = mxCreateCellMatrix(1, 1);
		if (!checkArrayPointer(valarray, __LINE__))
			return;
		mxSetCell(valarray, 0, mxCreateString(Value.c_str()));
		mxSetFieldByNumber(&Struct, 0, index, valarray);
	}

	static void insertSingleElementIntoStruct(mxArray &Struct, const std::string &ElementName, mxArray &Value)
	{
		int index = mxAddField(&Struct, ElementName.c_str());

		if (index == -1)
			Logger::Error("MATLABFileHandler: Could not add Field to struct! (Out of Memory?)");

		mxSetFieldByNumber(&Struct, 0, index, &Value);
	}

	//TODO create overload for complex type
	template<typename DataType, typename std::enable_if_t<std::is_arithmetic<DataType>::value, DataType*> =nullptr> //Numeric Types
	static void insert1DElementIntoStruct(mxArray &Struct, const std::string &ElementName, const std::vector<DataType> &Values)
	{
		int index = mxAddField(&Struct, ElementName.c_str());

		if (index == -1)
			Logger::Error("MATLABFileHandler: Could not add Field to struct! (Out of Memory?)");

		mxArray *valarray;
		valarray = mxCreateNumericMatrix(Values.size(), 1, MATLABClassFinder<DataType>::value, mxREAL);
		if (!checkArrayPointer(valarray, __LINE__))
			return;

		DataType * dataposition = mxGetPr(valarray);
		for (auto value : Values)
		{
			*dataposition++ = value;
		}

		mxSetFieldByNumber(&Struct, 0, index, valarray);
	};

	///EigenTypes
	template<typename EigenType,typename std::enable_if_t<std::is_floating_point<typename EigenType::Scalar>::value, typename EigenType::Scalar*> =nullptr> //Numeric Types
	static void insertSingleElementIntoStruct(mxArray &Struct, const std::string &ElementName, const EigenType &Values)
	{
		typedef typename EigenType::Scalar DataType;
		int index = mxAddField(&Struct, ElementName.c_str());

		if (index == -1)
			Logger::Error("MATLABFileHandler: Could not add Field to struct! (Out of Memory?)");

		mxArray *valarray;
		valarray = mxCreateNumericMatrix(Values.rows(), Values.cols(), MATLABClassFinder<DataType>::value, mxREAL);
		if (!checkArrayPointer(valarray, __LINE__))
			return;

		DataType * dataposition = mxGetPr(valarray);
		/* Inserting Data into Array */

		Eigen::Map<EigenType>(dataposition, Values.rows(), Values.cols()) = Values;

		mxSetFieldByNumber(&Struct, 0, index, valarray);
	};

	static void insert1DElementIntoStruct(mxArray &Struct, const std::string &ElementName, const std::vector<std::string> &Values)
	{
		int index = mxAddField(&Struct, ElementName.c_str());

		if (index == -1)
			Logger::Error("MATLABFileHandler: Could not add Field to struct! (Out of Memory?)");

		mxArray *valarray;
		valarray = mxCreateCellMatrix(1, Values.size()); // Strings in first row;
		if (!checkArrayPointer(valarray, __LINE__))
			return;
		
		size_t i = 0;
		for (auto &value : Values)
		{
			mxSetCell(valarray, i++, mxCreateString(value.c_str()));
			
		}
		mxSetFieldByNumber(&Struct, 0, index, valarray);
	}

	//TODO create overload for complex type
	template<typename EigenType, typename = typename std::enable_if_t<std::is_floating_point<typename EigenType::Scalar>::value, typename EigenType::Scalar>> //Numeric Types
	static void insertNDVectorIntoStruct(mxArray &Struct, const std::string &ElementName, std::vector<EigenType, Eigen::aligned_allocator<EigenType>> &Values)
	{
		typedef typename EigenType::Scalar DataType;
		int index = mxAddField(&Struct, ElementName.c_str());

		if (index == -1)
			Logger::Error("MATLABFileHandler: Could not add Field to struct! (Out of Memory?)");

		mxArray *valarray;
		valarray = mxCreateNumericMatrix(Values.begin()->rows(), Values.size(), MATLABClassFinder<DataType>::value, mxREAL);
		if (!checkArrayPointer(valarray, __LINE__))
			return;

		DataType * dataposition = mxGetPr(valarray);
		/* Inserting Data into Array */
		for (auto &val : Values)
		{
			Eigen::Map<EigenType>(dataposition, val.rows(), 1) = val;
			dataposition += val.rows();
		}

		mxSetFieldByNumber(&Struct, 0, index, valarray);
	}
	
	///insert mxArray int MAT File; Array gets invalidated if done!
	void insertArrayIntoMAT(mxArray &Array, const std::string Name)
	{
		int status = matPutVariable(_pMat, Name.c_str(), &Array); // This throws an expection and catches it itself!
		if (status != 0)
		{
			Logger::Error("MATLABFileHandler: Unable to put DataArray into MAT-file. Status is " + std::to_string(status));
		}
		mxDestroyArray(&Array);
	}



	inline static bool checkArrayPointer(mxArray *pArr, std::string caller, const int &lineno)
	{
		if (pArr == nullptr)
		{
			Logger::Error(caller + ": Pointer to mxArray not valid on Line: " + std::to_string(lineno));
			return false;
		}
		return true;
	}

	// Writes 1D named data to a struct within the MAT File
	template<typename NameContainer, typename DataContainer,
		typename = typename std::enable_if_t<std::is_arithmetic<typename DataContainer::value_type>::value, typename DataContainer::value_type>,
		typename = typename std::enable_if_t<std::is_same<typename NameContainer::value_type,std::string>::value> >							// Only for Numeric Types
	void writeSingleDataElementsToMATStruct(const std::string StructName, const NameContainer &NameOfElements, const DataContainer &ValueOfElements)
	{
		if (!checkOpen(__LINE__))
			return;

		if (NameOfElements.size() != ValueOfElements.size())
		{
			Logger::Error("MATLABFileHandler: Container size mismatch");
		}
		int Elements = (int) NameOfElements.size();
				
		//Create Fieldnames!
		std::vector<const char*> names(Elements);
		std::transform(NameOfElements.begin(), NameOfElements.end(), names.begin(), [](const std::string &s) -> const char* { return s.c_str(); });

		//Create MATLAB Struct 	
		mwSize ndims = 2;
		mwSize dims[2]{ 1,1 }; // Higher dimensional structs are a bit strange... looks like an array of structs (not what we normally want)
		mxArray *pStruct = mxCreateStructArray(ndims, dims, Elements,&names[0]);
		if (!checkArrayPointer(pStruct, __LINE__))
			return;
		
		//Fill MATLAB Struct 
		int i = 0;
		for (auto &Value : ValueOfElements)
		{
			addSingleValueToStruct(*pStruct, names[i++], Value);
		}
		insertArrayIntoMAT(*pStruct, StructName);
	}
	
	//// Writes 1D named data to a struct within the MAT File
	//template<typename DataType,	typename = typename std::enable_if<std::is_arithmetic<DataType>::value, DataType>::type>				// Only for Numeric Types
	//void writeSingleDataElementsToMATStruct(const std::string StructName, const std::map<std::string,DataType> &ElementsWithValue)
	//{
	//	if (!checkOpen(__LINE__))
	//		return;

	//	int Elements = (int)ElementsWithValue.size();
	//	std::vector<const char*> names(Elements)

	//	std::map<std::string, DataType>::iterator it = ElementsWithValue.begin();
	//	
	//	//Create Fieldnames!
	//	std::vector<const char*> names(Elements);
	//	std::transform(NameOfElements.begin(), NameOfElements.end(), names.begin(), [](const std::pair<std::string, DataType> pair) -> const char* { return (pair->first.c_str()); });

	//	//Create MATLAB Struct 	
	//	mwSize ndims = 2;
	//	mwSize dims[2]{ 1,1 };
	//	mxArray *pStruct = mxCreateStructArray(ndims, dims, Elements, &names[0]);
	//	if (!checkArrayPointer(pStruct, __LINE__))
	//		return;

	//	//Fill MATLAB Struct 
	//	int i = 0;
	//	for (auto &Value : ElementsWithValue)
	//	{
	//		addSingleValueToStruct(*pStruct, names[i++], Value);
	//	}

	//	insertArrayIntoMAT(*pStruct, StructName);
	//	mxDestroyArray(pStruct);
	//}

};