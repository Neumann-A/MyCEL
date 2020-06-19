cmake_minimum_required (VERSION 3.16)
project(Basic_Library VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
#extension to std in namespace stdext
#include_directories(stdext)
set(H_FILES_STDEXT  include/stdext/get_array_size.h
                    include/stdext/is_arithmetic_container.h
                    include/stdext/is_associative_container.h
                    include/stdext/is_boost_multiarray.h
                    include/stdext/is_callable.h
                    include/stdext/is_complex.h
                    include/stdext/is_container.h
                    include/stdext/is_detected.h
                    include/stdext/is_eigen3_type.h
                    include/stdext/is_memory_sequentiel_container.h
                    include/stdext/is_nested_arithmetic_container.h
                    include/stdext/is_nested_container.h
                    include/stdext/is_resizeable_container.h
                    include/stdext/is_sequentiel_container.h
                    include/stdext/is_string.h
                    include/stdext/std_extensions.h)

#some basic helpers
#include_directories(basics)
set(CPP_FILES_BASICS    src/basics/BasicIncludes.cpp
                        src/basics/GlobalParameters.cpp
                        src/basics/StartOptions.cpp)
set(H_FILES_BASICS      include/basics/BasicIncludes.h
                        include/basics/BasicMacros.h
                        include/basics/ComplexMacros.h
                        include/basics/GlobalParameters.h
                        include/basics/Logger.h
                        include/basics/NoCopy.h
                        include/basics/SimpleSmartEnum.h
                        include/basics/StartOptions.h
                        include/basics/ThreadManager.h
                        include/basics/Timer.h
                        include/basics/Typelist.h)

#some fundamental math helpers and functions
#include_directories(math)
set(H_FILES_MATH    include/math/ApproxJacobian.h
                    include/math/Coordinates.h
                    include/math/DistributionCalculator.h
                    include/math/DistributionHelper.h
                    include/math/Geometry.h
                    include/math/GSL_Implicit_Solver.h
                    include/math/GSL_Implicit_Solver_Derivative_Free.h
                    include/math/Implicit_Solver.h
                    include/math/include/math_constants.h
                    include/math/random_helpers.h
                    include/math/sincos.h)

#include_directories(utils)
set(CPP_FILES_UTILS src/utils/CoreInfo.cpp
                    src/utils/hpcenvreader.cpp
                    src/utils/ProcessorInformation.cpp)
set(H_FILES_UTILS   include/utils/CoreInfo.h
                    include/utils/HPCEnvReader.h
                    include/utils/ProcessorInformation.h
                    include/utils/ThreadDispatcher.h
                    include/utils/ThreadPool.h)

set(CPP_FILES_INTRIN )
set(H_FILES_INTRIN   include/intrin/svml_prolog.h
                     include/intrin/svml/avx_svml_include/intrin.h
                     include/intrin/svml/avx512_svml_include/intrin.h)

set(CPP_FILES_SIMD_RAND )
set(H_FILES_SIMD_RAND   include/simd_rand/constants.h
                        include/simd_rand/definitions.h
                        include/simd_rand/simd_lcg.h
                        include/simd_rand/simd_normal_dist.h)

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