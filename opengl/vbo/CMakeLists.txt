project(vbo)

set(srcs ${PROJECT_NAME}.cxx OpenGLSLHelper.cpp)

find_package(GLUT)
find_package(OpenGL)

add_executable(${PROJECT_NAME} ${srcs})

target_link_libraries(${PROJECT_NAME}
  GL
  glut
  GLU
  GLee)
