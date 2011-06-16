# Root cmake file.
cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)

project(3ds_viewer)

set(SRCS main.cxx)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME}
  vtkHybrid
  vtkIO
  vtkRendering
)
