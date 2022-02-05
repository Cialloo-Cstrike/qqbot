#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "mirai-cpp" for configuration ""
set_property(TARGET mirai-cpp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(mirai-cpp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmirai-cpp.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS mirai-cpp )
list(APPEND _IMPORT_CHECK_FILES_FOR_mirai-cpp "${_IMPORT_PREFIX}/lib/libmirai-cpp.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
