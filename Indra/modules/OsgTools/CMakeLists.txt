
#------------------Project name------------------.
PROJECT( OsgTools )


INCLUDE( ${CMAKE_MODULES_DIR}/Indra.cmake )


INCLUDE( ${CMAKE_MODULES_DIR}/FindOSG.cmake )

# List all the source files. 
#
SET(SOURCES 
 ./SG/OsgFind.cpp 
 ./Geom/OsgQuad.cpp 
 ./Geom/OsgDashboard.cpp 
)

#------------------List all the includes------------------  
INCLUDE_DIRECTORIES(../ ${OSG_INC_DIR}) 


#------------------Build shared library------------------ 
ADD_LIBRARY( OsgTools SHARED ${SOURCES} )


#------------------Set the library path------------------ 
TARGET_LINK_LIBRARIES( OsgTools ${OSG_LIB} )


#------------------Install------------------
INSTALL( TARGETS OsgTools DESTINATION ${Indra_SOURCE_DIR}/bin )

