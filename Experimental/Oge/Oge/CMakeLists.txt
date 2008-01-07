
INCLUDE( ${CMAKE_MODULES_DIR}/Oge.cmake )


PROJECT( Oge )


SET( LIB_NAME Oge )


OPTION( OGE_USE_OSG "Use OpenSceneGraph" ON )

IF( OGE_USE_OSG )
 INCLUDE( ${CMAKE_MODULES_DIR}/FindOSG.cmake ) 
 ADD_DEFINITIONS( "-DUSE_OSG" ) 
 INCLUDE_DIRECTORIES( ${OSG_INC_DIR} )
ENDIF( VEDA_USE_OSG )


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
 ./OgeBase/OgeOsg/OsgCamera.cpp
 ./OgeBase/OgeCore/OsgModel.cpp
 ./OgeBase/OgeCore/OsgView.cpp
 ./OgeBase/OgeCore/OsgViewer.cpp	
 ./OgeVrj/VrjCore/VrjAnalogInput.cpp
 ./OgeVrj/VrjCore/VrjDigitalInput.cpp
 ./OgeVrj/VrjCore/VrjPositionalInput.cpp
 ./OgeVrj/VrjDev/Gamepad.cpp
 ./OgeVrj/VrjOsg/VrjViewer.cpp
 ./Geom/OsgDashboard.cpp )

 

ADD_LIBRARY( ${LIB_NAME} SHARED ${SOURCES} )


IF( USE_OSG ) 
 TARGET_LINK_LIBRARIES( ${LIB_NAME}
                        ${OPENSCENEGRAPH_OSG_LIB}
                        ${OPENSCENEGRAPH_OSG_UTIL_LIB}
						${OPENSCENEGRAPH_OSG_DB_LIB} )
ENDIF( USE_OSG )


TARGET_LINK_LIBRARIES( ${LIB_NAME} ${VRJUGGLER_LIBS} )


INSTALL( TARGETS ${LIB_NAME} DESTINATION ${Oge_SOURCE_DIR}/bin )


