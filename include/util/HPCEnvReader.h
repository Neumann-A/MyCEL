///---------------------------------------------------------------------------------------------------
// file:		HPCEnvReader.h
//
// summary: 	Declares the hpc environment reader class
//
// Copyright (c) 2018 Alexander Neumann.
//
// author: Neumann
// date: 20.07.2018

#ifndef INC_HPCEnvReader_H
#define INC_HPCEnvReader_H
///---------------------------------------------------------------------------------------------------
#pragma once
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>
#include <iostream>
namespace utils
{
    struct HPCEnvReader
    {
    public:
        std::vector<std::size_t> AssignedCores;

        HPCEnvReader();

        template <std::size_t N>
        static std::unique_ptr<char[]> readEnviormentVariable(const char(&envvar)[N])
        {
            std::size_t reqSize;
            auto err = getenv_s(&reqSize, nullptr, 0, envvar);
            if (!(reqSize == 0))
            {
                auto readval = std::make_unique<char[]>(reqSize);
                if (readval)
                {
                    // Get the value of the environment variable.  
                    err = getenv_s(&reqSize, readval.get(), reqSize, envvar);

                    Log("EnvVar:\t", envvar, "\tis set to:\t", readval.get(),'\n');

                    return readval;
                }
                else
                {
                    Log("Unable to allocate Memory for EnvVar\n");
                }
                //free(readval);
            }
            else
            {
                Log("EnvVar:\t", envvar, "\tdoes not exist!\n");
            }
            return nullptr;
        }

        template<typename... Args>
        static void Log(Args&&... args)
        {
            (std::cout << ... << args);
        }

    private:

        static std::vector<std::size_t> createCoreList(char* envvar);
    };
}
#endif	// INC_HPCEnvReader_H
// end of HPCEnvReader.h
///---------------------------------------------------------------------------------------------------
