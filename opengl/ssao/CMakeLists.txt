cmake_minimum_required(VERSION 2.8.2)

project(ssao)

set(SRCS
  main.cpp
  objLoader.cpp
  objLoader.h
  TokenStream.h
  TokenStream.cpp
  OpenGLSLHelper.h
  OpenGLSLHelper.cpp
  OpenGLFbo.h
  OpenGLFbo.cpp
)

include_directories(/usr/include/GL
                    /usr/local/include
)

link_directories(/usr/local/lib
)

add_executable(${PROJECT_NAME} ${SRCS}
)

target_link_libraries(
  ${PROJECT_NAME}
  GL
  glut
  GLU
  GLee
)


