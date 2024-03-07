cmake_minimum_required(VERSION 3.18)

file(GLOB SOURCE_EXEC "*.cpp")
if (NOT SOURCE_EXEC)
  message(FATAL_ERROR "no source files for votess executable found.")
endif()

add_executable(test ${SOURCE_EXEC})
target_link_libraries(test PRIVATE hdf5 hdf5_cpp)
set_target_properties(test 
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
