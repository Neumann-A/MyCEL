cmake_minimum_required(VERSION 3.17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(NOT CMakeCS_FOUND)
    find_package(CMakeCS REQUIRED)
endif()

project("Project.MyCEL.cmakecs")
