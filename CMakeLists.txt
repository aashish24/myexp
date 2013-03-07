cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)

option(BUILD_OPENGL "Build OpenGL applications and tools" OFF)
option(BUILD_VTK "Build VTK applications and tools" OFF)
option(BUILD_CUDA "Build CUDA applications and tools" OFF)
option(BUILD_GDALTEST "Build GDAL test" OFF)

if(BUILD_OPENGL)
  add_subdirectory(opengl)
endif()

if(BUILD_VTK)
  add_subdirectory(vtk)
endif()

if(BUILD_CUDA)
  add_subdirectory(cuda)
endif()

if(BUILD_GDALTEST)
  add_subdirectory(gdaltest)
endif()
