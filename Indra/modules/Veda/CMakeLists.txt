
PROJECT( Veda )

SET( LIB_NAME Veda )


OPTION( USE_OSG "Use OpenSceneGraph" ON )

IF( BUILD_EXAMPLES )
 ADD_SUBDIRECTORY( examples )
ENDIF( BUILD_EXAMPLES )

 
INCLUDE( ${CMAKE_MODULES_DIR}/Indra.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindVRJuggler.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindOmniORB.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindCppDOM.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindGMTL.cmake )

#------@TODO: Read more about how to set flags in CMAKE and whether we really need these flags for Juggler app 
#SET( CMAKE_CXX_FLAGS "-DPIC -fPIC -DTWEEK_HAVE_CXX=1 -D__OSVERSION__=2 -D__linux__ -D__processor_unknown__ -fexceptions -pthread -O2 -fno-strict-aliasing -Wall -DHAVE_CONFIG_H" ) 
#SET( CMAKE_CXX_LINK_FLAGS "-pthread -Bdynamic" ) 


IF( USE_OSG )
 INCLUDE( ${CMAKE_MODULES_DIR}/FindOSG.cmake ) 
 ADD_DEFINITIONS( "-DHAVE_OSG" ) 
 INCLUDE_DIRECTORIES( ${OSG_INC_DIR} )
ENDIF( USE_OSG )


SET( SOURCES 
     ./Core/AppBase.cpp
     ./Core/Controller.cpp                  
     ./Core/Defs.cpp 
     ./Core/Globals.cpp                     
     ./Core/OsgBase.cpp 
     ./Core/SharedData.cpp                  
     ./Core/SubjectImpl.cpp                 
     ./Core/UserData.cpp                         
     ./Design/Navigation.cpp                  
     ./Design/OsgInteractor.cpp               
     ./Design/OssimInteractor.cpp                  
     ./Tweek/TweekSubject.cpp )  	


INCLUDE_DIRECTORIES( ../
		     ${GMTL_INC_DIR}
		     ${CPPDOM_INC_DIR}
		     ${OMNIORB_INC_DIR}		     
 		     ${VRJUGGLER_INCS} )

		     
SET( $ENV{JACORB_PATH} ${VJ_BASE_DIR}/bin )


ADD_CUSTOM_TARGET( CXX_IDL omniidl -bcxx -Wbh=.h,s=.cpp -I${VRJUGGLER_TWEEK_INC} -C./Tweek  ./Tweek/TweekSubject.idl )


ADD_LIBRARY( ${LIB_NAME} SHARED ${SOURCES} ) 


ADD_DEPENDENCIES( ${LIB_NAME} CXX_IDL )


LINK_INTERNAL( ${LIB_NAME} Neiv )


IF( USE_OSG )
 LINK_INTERNAL( ${LIB_NAME} OsgTools )
 TARGET_LINK_LIBRARIES( ${LIB_NAME}
                        ${OPENSCENEGRAPH_OSG_LIB}
                        ${OPENSCENEGRAPH_OSGUTIL_LIB}
			${OPENSCENEGRAPH_OSGDB_LIB} )
ENDIF( USE_OSG )

TARGET_LINK_LIBRARIES( ${LIB_NAME} 
		       ${VRJUGGLER_LIBS} )



INSTALL( TARGETS ${LIB_NAME} DESTINATION ${Indra_SOURCE_DIR}/bin )

