
PROJECT( Prithvi )


SET( LIB_NAME ${PROJECT} )


INCLUDE( ${CMAKE_MODULES_DIR}/Indra.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindOSG.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindOSSIM.cmake )


SET( SOURCES 
     ./Core/Planet.cpp )


set( CMAKE_CXX_FLAGS -DHAVE_OSSIM )


INCLUDE_DIRECTORIES( ../ 
		                 ${OSG_INC_DIR} 
		                 ${OSSIM_INC_DIR}
		                 ${OSSIMPLANET_INC_DIR} ) 


LINK_INTERNAL( ${LIB_NAME} Neiv )


ADD_LIBRARY( ${LIB_NAME} SHARED ${SOURCES} )


TARGET_LINK_LIBRARIES( ${LIB_NAME} ${OSG_LIB} ${OSSIM_LIB} ${OSSIMPLANET_LIB} )


INSTALL( TARGETS ${LIB_NAME} DESTINATION ${Indra_SOURCE_DIR}/bin )

