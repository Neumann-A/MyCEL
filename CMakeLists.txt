cmake_minimum_required (VERSION 3.16)
project(Basic_Library VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
#extension to std in namespace stdext
#include_directories(stdext)
set(H_FILES_STDEXT  stdext/get_array_size.h
                    stdext/is_arithmetic_container.h
                    stdext/is_associative_container.h
                    stdext/is_boost_multiarray.h
                    stdext/is_callable.h
                    stdext/is_complex.h
                    stdext/is_container.h
                    stdext/is_detected.h
                    stdext/is_eigen3_type.h
                    stdext/is_memory_sequentiel_container.h
                    stdext/is_nested_arithmetic_container.h
                    stdext/is_nested_container.h
                    stdext/is_resizeable_container.h
                    stdext/is_sequentiel_container.h
                    stdext/is_string.h
                    stdext/std_extensions.h)

#some basic helpers
#include_directories(basics)
set(CPP_FILES_BASICS    basics/BasicIncludes.cpp
                        basics/GlobalParameters.cpp
                        basics/StartOptions.cpp)
set(H_FILES_BASICS      basics/BasicIncludes.h
                        basics/BasicMacros.h
                        basics/ComplexMacros.h
                        basics/GlobalParameters.h
                        basics/Logger.h
                        basics/NoCopy.h
                        basics/SimpleSmartEnum.h
                        basics/StartOptions.h
                        basics/ThreadManager.h
                        basics/Timer.h
                        basics/Typelist.h)

#some fundamental math helpers and functions
#include_directories(math)
set(H_FILES_MATH    math/ApproxJacobian.h
                    math/Coordinates.h
                    math/DistributionCalculator.h
                    math/DistributionHelper.h
                    math/Geometry.h
                    math/GSL_Implicit_Solver.h
                    math/GSL_Implicit_Solver_Derivative_Free.h
                    math/Implicit_Solver.h
                    math/math_constants.h
                    math/random_helpers.h
                    math/sincos.h)

#include_directories(utils)
set(CPP_FILES_UTILS utils/CoreInfo.cpp
                    utils/hpcenvreader.cpp
                    utils/ProcessorInformation.cpp)
set(H_FILES_UTILS   utils/CoreInfo.h
                    utils/HPCEnvReader.h
                    utils/ProcessorInformation.h
                    utils/ThreadDispatcher.h
                    utils/ThreadPool.h)

set(CPP_FILES_INTRIN )
set(H_FILES_INTRIN   intrin/svml_prolog.h
                     intrin/svml/avx_svml_intrin.h
                     intrin/svml/avx512_svml_intrin.h)

set(CPP_FILES_SIMD_RAND )
set(H_FILES_SIMD_RAND   simd_rand/constants.h
                        simd_rand/definitions.h
                        simd_rand/simd_lcg.h
                        simd_rand/simd_normal_dist.h)

set(CPP_FILES ${CPP_FILES_STDEXT} ${CPP_FILES_BASICS} ${CPP_FILES_MATH} ${CPP_FILES_UTILS} ${CPP_FILES_INTRIN} ${CPP_FILES_SIMD_RAND})
set(H_FILES ${H_FILES_STDEXT} ${H_FILES_BASICS} ${H_FILES_MATH} ${H_FILES_UTILS} ${H_FILES_INTRIN} ${H_FILES_SIMD_RAND})

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE ${CPP_FILES} ${H_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

source_group("stdext\\headers"           FILES ${H_FILES_STDEXT})
source_group("stdext\\sources"           FILES ${CPP_FILES_STDEXT})
source_group("basics\\headers"           FILES ${H_FILES_BASICS})
source_group("basics\\sources"           FILES ${CPP_FILES_BASICS})
source_group("math\\headers"             FILES ${H_FILES_MATH})
source_group("math\\sources"             FILES ${CPP_FILES_MATH})
source_group("utils\\headers"            FILES ${H_FILES_UTILS})
source_group("utils\\sources"            FILES ${CPP_FILES_UTILS})
source_group("intrin\\headers"           FILES ${H_FILES_INTRIN})
source_group("intrin\\sources"           FILES ${CPP_FILES_INTRIN})
source_group("simd_rand\\headers"        FILES ${CPP_FILES_SIMD_RAND})
source_group("simd_rand\\sources"        FILES ${H_FILES_SIMD_RAND})

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-exports
        LIBRARY 
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE 
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES 
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT ${PROJECT_NAME}-exports
        FILE
            ${PROJECT_NAME}Targets.cmake
        NAMESPACE
            ${PROJECT_NAME}::
        DESTINATION
            ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

write_basic_package_version_file(${PROJECT_NAME}ConfigVersion.cmake COMPATIBILITY SameMajorVersion)

configure_package_config_file(
    ${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION 
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
install(FILES 
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION 
            ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME} 
)