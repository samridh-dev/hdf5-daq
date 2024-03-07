cmake_minimum_required(VERSION 3.18)

project(votess
  VERSION 0.1
  DESCRIPTION "a parallel multi-target voronoi tesselator"
  LANGUAGES CXX
)

include(cmake/include.cmake)
add_subdirectory(src)
