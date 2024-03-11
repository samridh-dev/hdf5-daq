cmake_minimum_required(VERSION 3.18)

include(cmake/unset_opts.cmake)
include(cmake/options.cmake)

project(test
  VERSION 0.1
  DESCRIPTION "a basic hdf5 interface for data acquisiton"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)

include(cmake/dependencies.cmake)
include(cmake/include.cmake)

add_subdirectory(src)
