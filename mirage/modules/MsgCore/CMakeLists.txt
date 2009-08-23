
SET(BUILD_SHARED_LIBS ON)
set(LIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${GLEW_LIBRARY})

include_directories(${MIRAGE_SOURCE_DIR}/Modules)
include_directories(${X_INC_DIR})
include_directories(${GLEW_INCLUDE_PATH})

SET (FILES	Drawable.cpp		GLSLShader.cpp		Geode.cpp				Referenced.cpp		StateAttribute.cpp	Uniform.cpp
GLSLAttribute.cpp		Geometry.cpp				StateSet.cpp		Viewer.cpp
GLSLProgram.cpp			Group.cpp		Node.cpp		Shader.cpp		
 	
	)

add_library(MsgCore ${FILES})
target_link_libraries(MsgCore ${LIBS})
