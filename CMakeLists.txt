cmake_minimum_required(VERSION 3.18)

include(cmake/unset_conf.cmake)
include(cmake/config.cmake)

project(test
  VERSION 0.1
  DESCRIPTION "a basic hdf5 interface for data acquisiton"
  LANGUAGES CXX
)

include(cmake/compiler_settings.cmake)

include(cmake/dependencies.cmake)
include(cmake/include.cmake)

add_subdirectory(src)

if (ENABLE_BUILD_LIBRARY)

  add_library(hdaq INTERFACE)
  target_include_directories(hdaq INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  target_link_libraries(hdaq INTERFACE hdf5 hdf5_cpp)

endif()
