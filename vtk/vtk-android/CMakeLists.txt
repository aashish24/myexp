
cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)

project(vtk-android)

find_package(VTK REQUIRED)
if(NOT VTK_FOUND)
  message("VTK not found")
else()
  include(${VTK_USE_FILE})
endif()

find_package(GLUT)
find_package(OpenGL)
find_path(GLM_INCLUDE_DIR REQUIRED)

set(SRCS
  vtk-android.cpp
  ../../opengl/common/OpenGLSLHelper.cpp
  )

include_directories(
  ../../opengl/common
  ${GLM_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME}
  vtkIO
  GL
  glut
  GLU
  GLee)
