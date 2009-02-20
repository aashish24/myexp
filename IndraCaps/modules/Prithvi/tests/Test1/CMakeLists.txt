
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
PROJECT( test1 )

#-----------------List all the source files----------------- 
SET( SOURCES ./main.cpp )

#----------------Set CXX Flags------------------
set( CMAKE_CXX_FLAGS -DHAVE_OSSIM )

#------------------Find------------------ 
FIND_LIBRARY( NEIV_LIB Neiv ../../../../bin )

#------------------Find------------------ 
FIND_LIBRARY( PRITHVI_LIB Prithvi ../../../../bin )

#------------------Find------------------ 
FIND_LIBRARY( OSG_LIB osg ${OSG_LIB_DIR} )

#------------------Find------------------ 
FIND_LIBRARY( OSSIM_LIB ossim ${OSSIM_LIB_DIR} )

#------------------Find------------------ 
FIND_LIBRARY( OSSIMPLANET_LIB ossimPlanet ${OSSIMPLANET_LIB_DIR} )

#------------------List all the includes------------------  
INCLUDE_DIRECTORIES( ./../../../ ) 

#------------------List all the includes------------------  
INCLUDE_DIRECTORIES( ${OSSIM_INC_DIR} ) 

#------------------List all the includes------------------  
INCLUDE_DIRECTORIES( ${OSSIMPLANET_INC_DIR} ) 

#------------------List all the includes------------------  
INCLUDE_DIRECTORIES( ../ ${OSG_INC_DIR} ) 

#------------------Link the libraries------------------ 
LINK_LIBRARIES( test1 Neiv Prithvi osg ossim ossimPlanet )

#------------------Build shared library------------------ 
ADD_EXECUTABLE( test1 ${SOURCES} )

#------------------Set the library path------------------ 
TARGET_LINK_LIBRARIES( test1 ${NEIV_LIB} ${PRITHVI_LIB} ${OSG_LIB} ${OSSIM_LIB} ${OSSIMPLANET_LIB} )

#------------------Install------------------
INSTALL( TARGETS test1 DESTINATION ../../../../bin )

