
set( CMAKE_INSTALL_PREFIX "./" )

#------Project name.
PROJECT( OsgTools )


#------List all the source files. 
SET( SOURCES 
 ./Base/Referenced.cpp )  

INCLUDE_DIRECTORIES( ../ )

ADD_LIBRARY( Neiv SHARED ${SOURCES} )

TARGET_LINK_LIBRARIES( Neiv )

INSTALL( TARGETS Neiv  DESTINATION ${Indra_SOURCE_DIR}/bin )

