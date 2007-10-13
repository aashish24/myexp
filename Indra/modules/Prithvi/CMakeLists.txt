
#------------------Project name------------------
PROJECT( Prithvi )

INCLUDE( ${CMAKE_MODULES_DIR}/Indra.cmake 
	 ${CMAKE_MODULES_DIR}/FindOSG.cmake
         ${CMAKE_MODULES_DIR}/FindOSSIM.cmake )


#-----------------List all the source files----------------- 
SET( SOURCES 
     ./Core/Planet.cpp )


#----------------Set CXX Flags------------------
set( CMAKE_CXX_FLAGS -DHAVE_OSSIM )


#------------------List all the includes------------------  
INCLUDE_DIRECTORIES( ../ 
		    ${OSG_INC_DIR} 
		    ${OSSIM_INC_DIR}
		    ${OSSIMPLANET_INC_DIR} ) 


#------------------Link the libraries------------------ 
LINK_INDRA( Prithvi Neiv )


#------------------Build shared library------------------ 
ADD_LIBRARY( Prithvi SHARED ${SOURCES} )


#------------------Set the library path------------------ 
TARGET_LINK_LIBRARIES( Prithvi ${OSG_LIB} ${OSSIM_LIB} ${OSSIMPLANET_LIB} )


#------------------Install------------------
INSTALL( TARGETS Prithvi DESTINATION ../../bin )

