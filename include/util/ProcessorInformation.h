///---------------------------------------------------------------------------------------------------
// file:		ProcessorInformation.h
//
// summary: 	Declares the processor information class
//
// Copyright (c) 2018 Alexander Neumann.
//
// author: Neumann
// date: 20.07.2018

#ifndef INC_ProcessorInformation_H
#define INC_ProcessorInformation_H
///---------------------------------------------------------------------------------------------------
#pragma once

//Silly guarding using the preprocessor
#ifndef WIN32_LEAN_AND_MEAN
#define INC_ProcessorInformation_H_WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define INC_ProcessorInformation_H_NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
//undef if needed.
#ifdef INC_ProcessorInformation_H_NOMINMAX
#undef NOMINMAX 
#endif
#ifdef INC_ProcessorInformation_H_WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#endif

namespace utils
{

    //Copied from somewhere out of the web (https://blogs.msdn.microsoft.com/oldnewthing/20131028-00/?p=2823)    
    class EnumLogicalProcessorInformation
    {
    public:
        EnumLogicalProcessorInformation(LOGICAL_PROCESSOR_RELATIONSHIP Relationship);
        ~EnumLogicalProcessorInformation();

        void MoveNext();

        SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *Current();

    private:
        SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX * m_pinfoBase;
        SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *m_pinfoCurrent;
        DWORD m_cbRemaining;
    };


}
#endif	// INC_ProcessorInformation_H
// end of ProcessorInformation.h
///---------------------------------------------------------------------------------------------------
