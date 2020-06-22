include(CMakeFindDependencyMacro)
find_dependency(VCPKG) # Try to use VCPKG if available
if(VCPKG_INSTALLED_DIR AND NOT CMAKE_PREFIX_PATH)
    set(CMakeCS_DIR "${VCPKG_INSTALLED_DIR}/share/CMakeCS" CACHE PATH "Path to CMakeCS")
    set(GTest_DIR "${CMakeCS_DIR}/../gtest" CACHE PATH "Path to GTest") 
    # Typically called before the first project() call
    # as such the toolchain file is not yet loaded
endif()
find_dependency(CMakeCS CONFIG)

find_package_handle_standard_args(CMakeCS CONFIG_MODE)