
#------Add debug build preprocessors.
IF( CMAKE_BUILD_TYPE STREQUAL "Debug" )
 ADD_DEFINITIONS( "-D_DEBUG" )
 SET( CMAKE_DEBUG_POSTFIX d )
ENDIF( CMAKE_BUILD_TYPE STREQUAL "Debug" )


#------Add release build preprocessors.
IF( CMAKE_BUILD_TYPE STREQUAL "Release" )
 ADD_DEFINTIONS( "-DNDEBUG" )
ENDIF( CMAKE_BUILD_TYPE STREQUAL "Release" )


#------Macro to facilitate automatic linking with debug or release builds for libs build by project. 
MACRO( LINK_INTERNAL TRGTNAME )
 FOREACH( LINKLIB ${ARGN} )
  TARGET_LINK_LIBRARIES( ${TRGTNAME} optimized "${LINKLIB}" debug "${LINKLIB}${CMAKE_DEBUG_POSTFIX}" )
 ENDFOREACH( LINKLIB )
ENDMACRO( LINK_INTERNAL TRGTNAME )

