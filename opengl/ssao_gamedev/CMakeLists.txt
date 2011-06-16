cmake_minimum_required(VERSION 2.8.2)

project(ssao_gamedev)

set(SRCS
  main.cpp
)

set(COMMON_SRCS
  ../common/objLoader.cpp
  ../common/objLoader.h
  ../common/TokenStream.h
  ../common/TokenStream.cpp
  ../common/OpenGLSLHelper.h
  ../common/OpenGLSLHelper.cpp
  ../common/OpenGLFbo.h
  ../common/OpenGLFbo.cpp
  ../common/TGA.cpp
  ../common/Trackball.cpp
)

include_directories(/usr/include/GL
                    /usr/local/include
                    ../common
)

link_directories(/usr/local/lib
)

add_executable(${PROJECT_NAME}
  ${SRCS}
  ${COMMON_SRCS}
)

target_link_libraries(
  ${PROJECT_NAME}
  GL
  glut
  GLU
  GLee
)
