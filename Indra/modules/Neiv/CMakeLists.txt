
set( CMAKE_INSTALL_PREFIX "./" )


# Project name.
#
PROJECT( OsgTools )

# List all the source files. 
#
SET( SOURCES 
./Base/Referenced.cpp  
)

INCLUDE_DIRECTORIES( ../ )

ADD_LIBRARY( Neiv SHARED ${SOURCES} )

INSTALL( TARGETS Neiv  DESTINATION ../../bin )

