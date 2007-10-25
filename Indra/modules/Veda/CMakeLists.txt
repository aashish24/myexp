
PROJECT( Veda )

SET( LIB_NAME Veda )


OPTION( USE_OSG "Use OpenSceneGraph" ON )

 

INCLUDE( ${CMAKE_MODULES_DIR}/FindVRJuggler.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindOmniORB.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindCppDOM.cmake )

SET( CMAKE_CXX_FLAGS "-pthread -DPIC -fPIC" ) 

IF( USE_OSG )
 SET( CMAKE_CXX_FLAGS "-DHAVE_OSG" ${CMAKE_CXX_FLAGS} ) 
ENDIF( USE_OSG )


SET( SOURCES 
     ./Core/Controller.cpp                  
     ./Core/Defs.cpp 
     ./Core/SharedData.cpp                  
     ./Core/SubjectImpl.cpp                 
     ./Core/UserData.cpp                    
     ./Core/Globals.cpp                     
     ./Design/Navigation.cpp                  
     ./Design/OsgInteractor.cpp               
     ./Design/OssimInteractor.cpp             
     ./Core/OsgBase.cpp                     
     ./Core/AppBase.cpp )  	


INCLUDE_DIRECTORIES( ./ )


ADD_LIBRARY( ${LIB_NAME} SHARED ${SOURCES} ) 


LINK_INTERNAL( ${LIB_NAME} Neiv )


IF( USE_OSG )
 LINK_INTERNAL( ${LIB_NAME} OsgTools )
 TARGET_LINK_LIBRARIES( ${LIB_NAME}
                        ${OSG_LIB}
                        ${OSG_UTIL_LIB}
			${OSG_DB_LIB} )
ENDIF( USE_OSG )

TARGET_LINK_LIBRARIES( ${LIB_NAME} 
			${VRJ_LIB}
			${VRJ_OGL_LIB}
			${GADGET_LIB}
			${JCCL_LIB}
			${TWEEK_LIB} )



INSTALL( TARGETS ${LIB_NAME} DESTINATION ${Indra_SOURCE_DIR}/bin )

