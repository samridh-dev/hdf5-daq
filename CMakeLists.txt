cmake_minimum_required(VERSION 3.18)

project(test
  VERSION 0.1
  DESCRIPTION "a basic hdf5 interface for data acquisiton"
  LANGUAGES CXX
)

include(cmake/dependencies.cmake)
include(cmake/include.cmake)

add_subdirectory(src)
