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

if (ENABLE_BUILD_LIBRARY)

  add_library(hdaq INTERFACE)
  target_link_libraries(hdaq INTERFACE hdf5 hdf5_cpp)
  target_include_directories(hdaq INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )

endif()
