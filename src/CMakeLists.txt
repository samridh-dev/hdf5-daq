cmake_minimum_required(VERSION 3.18)

if (ENABLE_BUILD_EXAMPLE)

  file(GLOB SOURCE_EXEC "*.cpp")
  if (NOT SOURCE_EXEC)
    message(FATAL_ERROR "no source files for votess executable found.")
  endif()

  add_executable(hdf5daq_example ${SOURCE_EXEC})
  target_link_libraries(hdf5daq_example PRIVATE hdf5 hdf5_cpp)
  set_target_properties(hdf5daq_example 
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
  )

endif()
