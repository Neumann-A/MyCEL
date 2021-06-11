include(FetchContent)

find_file(CMakeJSON_INCLUDE_FILE NAMES "CMakeJSON.cmake" PATHS share cmake share/cmake PATH_SUFFIXES CMakeJSON)

if(NOT CMakeJSON_INCLUDE_FILE AND NOT CMakeJSON_FOUND)
  FetchContent_Declare(
    CMakeJSON  
    GIT_REPOSITORY https://github.com/Neumann-A/CMakeJSON.git
    GIT_TAG        f18ca04c22ed23dd08be154af95c4da1c7c1e5db
  )

  FetchContent_GetProperties(CMakeJSON)
  string(TOLOWER "CMakeJSON" lcName)

  if(NOT ${lcName}_POPULATED)
      FetchContent_Populate(CMakeJSON)
      set(CMakeJSON_INCLUDE_FILE "${${lcName}_SOURCE_DIR}/CMakeJSON/CMakeJSON.cmake")
  endif()
endif()

if(CMakeJSON_INCLUDE_FILE AND NOT CMakeJSON_FOUND)
  include("${CMakeJSON_INCLUDE_FILE}")
  set(CMakeJSON_FOUND TRUE)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CMakeJSON FOUND_VAR CMakeJSON_FOUND REQUIRED_VARS CMakeJSON_INCLUDE_FILE)