# Root cmake file.
cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)

project(vector_viewer)

# VTK is required.
find_package(VTK REQUIRED)
if(VTK_FOUND)
  include(${VTK_USE_FILE})
else(VTK_FOUND)
  message(FATAL_ERROR, "VTK is required")
endif(VTK_FOUND)

find_package(GDAL REQUIRED)

set(SRCS main.cxx vtkOGRReader.cxx)

include_directories(${GDAL_CONFIG}/include)
link_directories(${GDAL_CONFIG}/lib)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME}
  vtkRendering
  gdal
)
