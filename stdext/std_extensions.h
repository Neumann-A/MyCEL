///---------------------------------------------------------------------------------------------------
// file:		stdext\std_extensions.h
//
// summary: 	Includes all std extension headers
//
// Copyright (c) 2017 Alexander Neumann.
//
// author: Alexander
// date: 06.08.2017

#ifndef INC_std_extensions_H
#define INC_std_extensions_H
///---------------------------------------------------------------------------------------------------
#pragma once

#include <type_traits>

//#include "is_callable.h" (not need -> use stdext::is_detected instead)
#include "is_container.h"
#include "is_detected.h"
#include "is_string.h"
#include "is_arithmetic_container.h"
#include "is_resizeable_container.h"
#include "is_associative_container.h"
#include "is_memory_sequentiel_container.h"

#include "is_nested_container.h"
#include "is_nested_arithmetic_container.h"

#include "is_eigen3_type.h"
#include "get_array_size.h"

#endif	// INC_std_extensions_H
// end of stdext\std_extensions.h
///---------------------------------------------------------------------------------------------------
