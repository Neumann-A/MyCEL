cmake_minimum_required(VERSION 3.19)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(NOT CMakeJSON_FOUND)
    find_package(CMakeJSON REQUIRED)
endif()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_C_VISIBILITY_PRESET hidden)

project("MyCEL.json")

add_subdirectory(tests)