# Root cmake file.
cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)

project(topoly_viewer)

# VTK is required.
find_package(VTK REQUIRED)
if(VTK_FOUND)
  include(${VTK_USE_FILE})
else(VTK_FOUND)
  message(FATAL_ERROR, "VTK is required")
endif(VTK_FOUND)

set(SRCS TestAashish.cxx)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME}
  vtkRendering
)
