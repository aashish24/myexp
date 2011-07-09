
cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)

find_package(VTK REQUIRED)
if(NOT VTK_FOUND)
  message("VTK not found")
else()
  include(${VTK_USE_FILE})
endif()

