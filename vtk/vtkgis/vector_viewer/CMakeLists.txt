# Root cmake file.
cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)

project(vector_viewer)

find_package(GDAL REQUIRED)

set(SRCS main.cxx vtkOGRReader.cxx)

include_directories(${GDAL_CONFIG}/include)
link_directories(${GDAL_CONFIG}/lib)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME}
  vtkGeovis
  vtkRendering
  gdal
)
