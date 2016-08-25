
#include "..\Headers\MATLABFileHandler.h"


void MATLABFileHandler::openMat(const std::string filename)
{
	if (checkAlreadyOpen())
		return;

	_filename = filename;
	try
	{
		_pMat = matOpen(_filename.c_str(), "r");
	}
	catch (std::exception& e)
	{
		Logger::Error(e.what());
		Logger::Error("MATLABFileHandler: matOpen threw an exception");
	}
	catch (...)
	{
		Logger::Error("MATLABFileHandler: matOpen threw an exception");
	}
	checkMatPointer(__LINE__);
};

void MATLABFileHandler::createMat(const std::string filename)
{
	if (checkAlreadyOpen())
		return;

	_filename = filename;
	try
	{
		_pMat = matOpen(_filename.c_str(), "w"); // Overwriting existing file
	}
	catch (std::exception& e)
	{
		Logger::Error(e.what());
		Logger::Error("MATLABFileHandler: matOpen threw an exception");
	}
	catch (...)
	{
		Logger::Error("MATLABFileHandler: matOpen threw an exception");
	}
	checkMatPointer(__LINE__);
};

void MATLABFileHandler::updateOrCreateMat(const std::string filename)
{
	if (checkAlreadyOpen())
		return;

	_filename = filename;
	try
	{
		_pMat = matOpen(_filename.c_str(), "u"); // Overwriting existing file
	}
	catch (std::exception& e)
	{
		Logger::Error(e.what());
		Logger::Error("MATLABFileHandler: matOpen threw an exception");
	}
	catch (...)
	{
		Logger::Error("MATLABFileHandler: matOpen threw an exception");
	}

	checkMatPointer(__LINE__);
};

mxArray& MATLABFileHandler::createMATLABStruct()
{
	mwSize ndims = 2;
	mwSize dims[2]{ 1,1 }; // Higher dimensional structs are a bit strange... looks like an array of structs (not what we normally want)
	mxArray *pStruct = mxCreateStructArray(ndims, dims, 0, nullptr);
	checkArrayPointer(pStruct, __LINE__);
	return *pStruct;
}

void MATLABFileHandler::closeMat()
{
	if (!_isOpen.exchange(false))
	{
		Logger::Error("MATLABFileHandler: MAT File already closed!");
		return;
	}
	else
	{
		if (matClose(_pMat) != 0)
		{
			Logger::Error("Error closing MAT-file %s", _filename.c_str());
			return;
		}
	}
	_pMat = nullptr; // resetting pointer!
};