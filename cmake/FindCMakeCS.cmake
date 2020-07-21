function(find_package_noise_args OUT_VAR)
    set(PACKAGE_REQUIRED )
    if(${CMAKE_FIND_PACKAGE_NAME}_FIND_REQUIRED)
        set(PACKAGE_REQUIRED REQUIRED)
    endif()
    set(PACKAGE_QUITE)
    if(${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
        set(PACKAGE_QUITE QUITE)
    endif()
    set(${OUT_VAR} ${PACKAGE_QUITE} ${PACKAGE_REQUIRED})
endfunction()

find_package_noise_args(NOISE_ARGS)

find_package(VCPKG ${NOISE_ARGS}) # Try to use VCPKG if available
cmake_print_variables(VCPKG_ROOT VCPKG_TARGET_TRIPLET CMAKE_TOOLCHAIN_FILE VCPKG_INSTALLED_DIR CMAKE_PREFIX_PATH)
if(VCPKG_INSTALLED_DIR AND NOT CMAKE_PREFIX_PATH MATCHES VCPKG_INSTALLED_DIR)
    if(NOT CMakeCS_DIR)
        set(_FORCE FORCE)
    endif()
    set(CMakeCS_DIR "${VCPKG_INSTALLED_DIR}/share/CMakeCS" CACHE PATH "Path to CMakeCS" ${_FORCE})
    set(GTest_DIR "${VCPKG_INSTALLED_DIR}/share/gtest" CACHE PATH "Path to GTest" ${_FORCE}) 
    unset(_FORCE)
    # Typically called before the first project() call
    # as such the toolchain file is not yet loaded
endif()
cmake_print_variables(CMakeCS_DIR GTest_DIR)
find_package(CMakeCS ${NOISE_ARGS} CONFIG)

find_package_handle_standard_args(CMakeCS CONFIG_MODE)