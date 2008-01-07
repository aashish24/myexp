
PROJECT( Test1_VrjViewer )

SET( APP_NAME Test1_VrjViewer )


OPTION( USE_OSG "Use OpenSceneGraph" ON )

 
INCLUDE( ${CMAKE_MODULES_DIR}/Oge.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindVRJuggler.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindOmniORB.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindCppDOM.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindGMTL.cmake )

#------Lets do more study on how to set flags in CMAKE
#SET( CMAKE_CXX_FLAGS "-fexceptions -pthread -Wall -DHAVE_CONFIG_H -O2 -fno-strict-aliasing -DJUGGLER_OPT -DNDEBUG -fno-strict-aliasing  -DTWEEK_HAVE_CXX=1 -D__OSVERSION__=2 -D__linux__ -D__processor_unknown__" ) 
#SET( CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -pthread -Bdynamic" ) 


IF( USE_OSG )
 INCLUDE( ${CMAKE_MODULES_DIR}/FindOSG.cmake ) 
 ADD_DEFINITIONS( "-DUSE_OSG" ) 
 INCLUDE_DIRECTORIES( ${OSG_INC_DIR} )
ENDIF( USE_OSG )


SET( SOURCES 
     ./MyApp.cpp
     ./main.cpp )  	


INCLUDE_DIRECTORIES( ${Indra_SOURCE_DIR}/modules
		     "$ENV{BOOST_INC_DIR}"
		     ${GMTL_INC_DIR}
		     ${CPPDOM_INC_DIR}
		     ${OMNIORB_INC_DIR}		     
 		     ${VRJUGGLER_INCS} )

		     

ADD_EXECUTABLE( ${APP_NAME} ${SOURCES} ) 


LINK_INTERNAL( ${APP_NAME} Oge )


IF( USE_OSG )
 LINK_INTERNAL( ${APP_NAME} OsgTools )
 TARGET_LINK_LIBRARIES( ${APP_NAME}
                        ${OPENSCENEGRAPH_OSG_LIB}
                        ${OPENSCENEGRAPH_OSGUTIL_LIB}
			            ${OPENSCENEGRAPH_OSGDB_LIB} )
ENDIF( USE_OSG )

TARGET_LINK_LIBRARIES( ${APP_NAME} 
		       ${CPPDOM_LIB}
		       ${OMNIORB_LIB}
		       ${OMNIDYNAMIC_LIB}
		       ${OMNITHREAD_LIB}
		       ${VRJUGGLER_LIBS} )



INSTALL( TARGETS ${APP_NAME} DESTINATION ${OGE_ROOT_SOURCE_DIR}/bin )

