include(CMakePrintHelpers)
option(USE_VCPKG_TOOLCHAIN "Use VCPKG toolchain; Switching this option requires a clean reconfigure" ON) 

if(USE_VCPKG_TOOLCHAIN)
    if(NOT VCPKG_TARGET_TRIPLET)
        if(DEFINED ENV{VCPKG_DEFAULT_TRIPLET})
            set(VCPKG_TARGET_TRIPLET "${VCPKG_DEFAULT_TRIPLET}" CACHE STRING "" FORCE)
        elseif(WIN32)
            set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "" FORCE)
        elseif(MSYS)
            set(VCPKG_TARGET_TRIPLET "x64-mingw" CACHE STRING "" FORCE)
        elseif(APPLE)
            set(VCPKG_TARGET_TRIPLET "x64-osx" CACHE STRING "" FORCE)
        elseif(UNIX)
            set(VCPKG_TARGET_TRIPLET "x64-linux" CACHE STRING "" FORCE)
        endif()
    endif()
    list(APPEND VCPKG_HINTS "${CMAKE_SOURCE_DIR}/../vcpkg/;${CMAKE_SOURCE_DIR}/vcpkg/;${CMAKE_BINARY_DIR}/../../vcpkg/;${CMAKE_BINARY_DIR}/../vcpkg/;${CMAKE_BINARY_DIR}/vcpkg/")
    find_path(VCPKG_ROOT NAMES .vcpkg-root HINTS ${VCPKG_HINTS} PATHS "./vcpkg" "./../vcpkg" "./vcpkg" "./../../vcpkg" $ENV{VCPKG_ROOT})
    if(EXISTS "${VCPKG_ROOT}")
        if(NOT CMAKE_TOOLCHAIN_FILE AND USE_VCPKG_TOOLCHAIN)      
            set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
        endif()
        set(VCPKG_INSTALLED_DIR "${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}" CACHE PATH "")
        if(NOT EXISTS "${VCPKG_INSTALLED_DIR}")
            message(STATUS "VCPKG with triplet ${VCPKG_TARGET_TRIPLET} seems to be empty!")
        endif()
        cmake_print_variables(VCPKG_ROOT VCPKG_TARGET_TRIPLET CMAKE_TOOLCHAIN_FILE)
    elseif(VCPKG_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find VCPKG! ${VCPKG_ROOT} with hints: ${VCPKG_HINTS}")
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(VCPKG REQUIRED_VARS "VCPKG_INSTALLED_DIR;VCPKG_ROOT;VCPKG_TARGET_TRIPLET")