#pragma once

#include <algorithm>
#include <string>

//#include <engine.h> //To connect to matlab engine (we dont work directly with matlab so does not matter)
//MATLAB includes
#include <mat.h>
#pragma comment (lib, "libmx.lib")
#pragma comment (lib, "libeng.lib")
#pragma comment (lib, "libmex.lib")
#pragma comment (lib, "libmat.lib")
//Needs the following PATH = C:\Program Files\Matlab\R2015b\bin\win64; %PATH%

typedef std::integral_constant<mxClassID, mxUNKNOWN_CLASS>	MATLAB_UnknownClass;
typedef std::integral_constant<mxClassID, mxCELL_CLASS>		MATLAB_CellClass;
typedef std::integral_constant<mxClassID, mxSTRUCT_CLASS>	MATLAB_StructClass;
typedef std::integral_constant<mxClassID, mxLOGICAL_CLASS>	MATLAB_LogicalClass;
typedef std::integral_constant<mxClassID, mxCHAR_CLASS>		MATLAB_CharClass;
typedef std::integral_constant<mxClassID, mxVOID_CLASS>		MATLAB_VoidClass;
typedef std::integral_constant<mxClassID, mxDOUBLE_CLASS>	MATLAB_DoubleClass;
typedef std::integral_constant<mxClassID, mxSINGLE_CLASS>	MATLAB_SingleClass;
typedef std::integral_constant<mxClassID, mxINT8_CLASS>		MATLAB_Int8Class;
typedef std::integral_constant<mxClassID, mxUINT8_CLASS>	MATLAB_UInt8Class;
typedef std::integral_constant<mxClassID, mxINT16_CLASS>	MATLAB_Int16Class;
typedef std::integral_constant<mxClassID, mxUINT16_CLASS>	MATLAB_UInt16Class;
typedef std::integral_constant<mxClassID, mxINT32_CLASS>	MATLAB_Int32Class;
typedef std::integral_constant<mxClassID, mxUINT32_CLASS>	MATLAB_UInt32Class;
typedef std::integral_constant<mxClassID, mxINT64_CLASS>	MATLAB_Int64Class;
typedef std::integral_constant<mxClassID, mxUINT64_CLASS>	MATLAB_UInt64Class;
typedef std::integral_constant<mxClassID, mxFUNCTION_CLASS>	MATLAB_FunctionClass;
typedef std::integral_constant<mxClassID, mxOPAQUE_CLASS>	MATLAB_OpaqueClass;
typedef std::integral_constant<mxClassID, mxOBJECT_CLASS>	MATLAB_ObjectClass;
typedef std::integral_constant<mxClassID, mxINDEX_CLASS>	MATLAB_IndexClass;


template<typename T>
struct MATLABClassFinder : MATLAB_UnknownClass {};

template<>
struct MATLABClassFinder<std::string> : MATLAB_CellClass {};

template<>
struct MATLABClassFinder<bool> : MATLAB_LogicalClass {};


template<>
struct MATLABClassFinder<uint8_t> : MATLAB_UInt8Class {};

template<>
struct MATLABClassFinder<int8_t> : MATLAB_Int8Class {};

template<>
struct MATLABClassFinder<uint16_t> : MATLAB_UInt16Class {};

template<>
struct MATLABClassFinder<int16_t> : MATLAB_Int16Class {};

template<>
struct MATLABClassFinder<uint32_t> : MATLAB_UInt32Class {};
template<>
struct MATLABClassFinder<unsigned long> : MATLAB_UInt32Class {};

template<>
struct MATLABClassFinder<int32_t> : MATLAB_Int32Class {};
template<>
struct MATLABClassFinder<long> : MATLAB_Int32Class {};

template<>
struct MATLABClassFinder<uint64_t> : MATLAB_UInt64Class {};

template<>
struct MATLABClassFinder<int64_t> : MATLAB_Int64Class {};

template<>
struct MATLABClassFinder<double> : MATLAB_DoubleClass {};

template<>
struct MATLABClassFinder<float> : MATLAB_SingleClass {};