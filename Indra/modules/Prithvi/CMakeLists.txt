
set( CMAKE_INSTALL_PREFIX "./" )
set( OSG_LIB_DIR "$ENV{OSG_LIB_DIR}" )
set( OSG_INC_DIR "$ENV{OSG_INC_DIR}" )

set( OSG_LIB_DIR "$ENV{OSG_LIB_DIR}" )
set( OSG_INC_DIR "$ENV{OSG_INC_DIR}" )

set( OSSIM_LIB_DIR "$ENV{OSSIM_LIB_DIR}" )
set( OSSIM_INC_DIR "$ENV{OSSIM_INC_DIR}" )

set( OSSIMPLANET_LIB_DIR "$ENV{OSSIMPLANET_LIB_DIR}" )
set( OSSIMPLANET_INC_DIR "$ENV{OSSIMPLANET_INC_DIR}" )

#------------------Project name------------------
PROJECT( Prithvi )

#-----------------List all the source files----------------- 
SET( SOURCES 
./Core/Planet.cpp
)

#----------------Set CXX Flags------------------
set( CMAKE_CXX_FLAGS -DHAVE_OSSIM )



#------------------Find------------------ 
FIND_LIBRARY( OSG_LIB osg ${OSG_LIB_DIR} )

#------------------Find------------------ 
FIND_LIBRARY( OSSIM_LIB ossim ${OSSIM_LIB_DIR} )

#------------------Find------------------ 
FIND_LIBRARY( OSSIMPLANET_LIB ossimPlanet ${OSSIMPLANET_LIB_DIR} )

#------------------List all the includes------------------  
INCLUDE_DIRECTORIES( ../ ${OSG_INC_DIR} ${OSSIM_INC_DIR}
${OSSIMPLANET_INC_DIR} ) 

#------------------Link the libraries------------------ 
LINK_LIBRARIES( Prithvi osg ossim ossimPlanet )

#------------------Build shared library------------------ 
ADD_LIBRARY( Prithvi SHARED ${SOURCES} )


#------------------Set the library path------------------ 
TARGET_LINK_LIBRARIES( Prithvi ${OSG_LIB} ${OSSIM_LIB} ${OSSIMPLANET_LIB} )

#------------------Install------------------
INSTALL( TARGETS Prithvi DESTINATION ../../bin )

