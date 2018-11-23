cmake_minimum_required (VERSION 3.4)
project(Basic_Library CXX)

#extension to std in namespace stdext
include_directories(stdext)
file(GLOB CPP_FILES_STDEXT stdext/*.cpp)
file(GLOB H_FILES_STDEXT stdext/*.h)

#some basic helpers
include_directories(basics)
file(GLOB CPP_FILES_BASICS basics/*.cpp)
file(GLOB H_FILES_BASICS basics/*.h)

#some fundamental math helpers and functions
include_directories(math)
file(GLOB CPP_FILES_MATH math/*.cpp)
file(GLOB H_FILES_MATH math/*.h)

include_directories(utils)
file(GLOB CPP_FILES_UTILS utils/*.cpp)
file(GLOB H_FILES_UTILS utils/*.h)

set(CPP_FILES ${CPP_FILES_STDEXT} ${CPP_FILES_BASICS} ${CPP_FILES_MATH} ${CPP_FILES_UTILS})
set(H_FILES ${H_FILES_STDEXT} ${H_FILES_BASICS} ${H_FILES_MATH}  ${H_FILES_UTILS})

add_library(${PROJECT_NAME} STATIC ${CPP_FILES} ${H_FILES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

source_group("stdext\\headers"        FILES ${H_FILES_STDEXT})
source_group("stdext\\sources"        FILES ${CPP_FILES_STDEXT})
source_group("basics\\headers"        FILES ${H_FILES_BASICS})
source_group("basics\\sources"        FILES ${CPP_FILES_BASICS})
source_group("math\\headers"       	 FILES ${H_FILES_MATH})
source_group("math\\sources"       	 FILES ${CPP_FILES_MATH})
source_group("utils\\headers"       	 FILES ${H_FILES_UTILS})
source_group("utils\\sources"       	 FILES ${CPP_FILES_UTILS})

# Required on Unix OS family to be able to be linked into shared libraries.
set_target_properties(${PROJECT_NAME}
                      PROPERTIES POSITION_INDEPENDENT_CODE ON)

if(UNIX)
find_package(Threads)
endif()					  
					  
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

# Expose Basic_Library's public includes to other
# subprojects through cache variable.
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR} CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
					  
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/lib)
