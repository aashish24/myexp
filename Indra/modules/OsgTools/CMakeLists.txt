
set( CMAKE_INSTALL_PREFIX "./" )
set( OSG_LIB_DIR "$ENV{OSG_LIB_DIR}" )
set( OSG_INC_DIR "$ENV{OSG_INC_DIR}" )


# Project name.
#
PROJECT( OsgTools )

# List all the source files. 
#
SET( SOURCES 
./SG/OsgFind.cpp 
./Geom/OsgQuad.cpp 
./Geom/OsgDashboard.cpp 
)


# Find. 
#
FIND_LIBRARY( OSG_LIB osg ${OSG_LIB_DIR} )


# List all the includes. 
#
INCLUDE_DIRECTORIES( ../ ${OSG_INC_DIR} ) 


# Link the libraries. 
#
#LINK_LIBRARIES( OsgTools osg )


ADD_LIBRARY( OsgTools SHARED ${SOURCES} )


# Set the library path. 
#
TARGET_LINK_LIBRARIES( OsgTools ${OSG_LIB} )


INSTALL( TARGETS OsgTools DESTINATION ../../bin )

