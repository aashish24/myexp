
SET(BUILD_SHARED_LIBS ON)
set(LIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${GLEW_LIBRARY})

include_directories(${MIRAGE_SOURCE_DIR}/Modules)
include_directories(${X_INC_DIR})
include_directories(${GLEW_INCLUDE_PATH})

SET (FILES	FileRead.cpp		ObjReader.cpp			TextFileReadWrite.cpp)

add_library(MsgDB ${FILES})
target_link_libraries(MsgDB ${LIBS})
