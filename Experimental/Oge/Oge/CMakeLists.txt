
INCLUDE( ${CMAKE_MODULES_DIR}/Oge.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindVRJuggler.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindOmniORB.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindCppDOM.cmake )
INCLUDE( ${CMAKE_MODULES_DIR}/FindGMTL.cmake )



PROJECT( Oge )


SET( LIB_NAME Oge )


OPTION( OGE_USE_OSG "Use OpenSceneGraph" ON )


IF( OGE_USE_OSG )
 INCLUDE( ${CMAKE_MODULES_DIR}/FindOSG.cmake ) 
 ADD_DEFINITIONS( "-DUSE_OSG" ) 
 INCLUDE_DIRECTORIES( ${OSG_INC_DIR} )
ENDIF( OGE_USE_OSG )



INCLUDE_DIRECTORIES( ${OGE_ROOT_SOURCE_DIR} )
INCLUDE_DIRECTORIES( ${GMTL_INC_DIR} )
INCLUDE_DIRECTORIES( ${CPPDOM_INC_DIR} )
INCLUDE_DIRECTORIES( ${OMNIORB_INC_DIR} )
INCLUDE_DIRECTORIES( ${VRJUGGLER_INCS} )



SET( SOURCES 
 ./OgeBase/OgeContexts/DefaultInterfaceContext.cpp
 ./OgeBase/OgeCore/Camera.cpp
 ./OgeBase/OgeCore/Event.cpp
 ./OgeBase/OgeCore/Input.cpp
 ./OgeBase/OgeCore/InputCallback.cpp
 ./OgeBase/OgeCore/MemberFunctor.cpp
 ./OgeBase/OgeCore/Model.cpp
 ./OgeBase/OgeCore/Referenced.cpp
 ./OgeBase/OgeCore/View.cpp
 ./OgeOsg/OsgCore/OsgCamera.cpp
 ./OgeOsg/OsgCore/OsgModel.cpp
 ./OgeOsg/OsgCore/OsgView.cpp
 ./OgeOsg/OsgCore/OsgViewer.cpp	
 ./OgeVrj/VrjCore/VrjDigitalInput.cpp
 ./OgeVrj/VrjCore/VrjAnalogInput.cpp
 ./OgeVrj/VrjCore/VrjPositionInput.cpp
 ./OgeVrj/VrjDev/Gamepad.cpp
 ./OgeVrj/VrjOsg/VrjViewer.cpp )



ADD_LIBRARY( ${LIB_NAME} SHARED ${SOURCES} )


IF( USE_OSG ) 
 TARGET_LINK_LIBRARIES( ${LIB_NAME}
                        ${OPENSCENEGRAPH_OSG_LIB}
                        ${OPENSCENEGRAPH_OSG_UTIL_LIB}
  			${OPENSCENEGRAPH_OSG_DB_LIB} )
ENDIF( USE_OSG )


TARGET_LINK_LIBRARIES( ${LIB_NAME} ${VRJUGGLER_LIBS} )


INSTALL( TARGETS ${LIB_NAME} DESTINATION ${OGE_ROOT_SOURCE_DIR}/bin )


