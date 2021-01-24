#pragma once

#include <exception>
#include "PreprocessorMakros.h"

#define SIMPLE_SMARTENUM_DEFINE(Type, ...) enum class Type { __VA_ARGS__ };    \
    constexpr const char * Type##Array [] { EVAL(MAP(LISTNAME,NAME , __VA_ARGS__)) }; \
    const Type get##Type##FromString(const char* str) \
    {				                      		\
        for (unsigned int i = 0; i < static_cast<unsigned int>(ARG_COUNT(__VA_ARGS__)); ++i)    \
        if (!strcmp(Type##Array[i], str))			\
            return static_cast<Type>(i);			\
        throw std::invalid_argument(EVAL(OBSTRUCT(NAME)(SIMPLE_SMARTENUM_THROW_INV_ARG(Type)))); \
    }
#define SIMPLE_SMARTENUM_THROW_INV_ARG(TypeName) Passed invalid string to get ##TypeName## FromString:
#define get_SIMPLE_SMARTENUM_FROM_CHAR(Type,Name) get##Type##FromString(Name)
#define get_SIMPLE_SMARTENUM_AS_CHAR(Type, Value) Type##Array[static_cast<unsigned int>(Value)]
