
SET( VJ_INC_DIR  $ENV{VJ_BASE_DIR}/include )
SET( VJ_BASE_DIR $ENV{VJ_BASE_DIR} )


FIND_LIBRARY( VRJ_LIB, vrj
		          ${VJ_BASE_DIR}/lib64
		          ${VJ_BASE_DIR}/lib
		          /usr/local/lib64
		          /usr/local/lib )
		     
IF( ${VRJ_LIB} )
  SET( VRJUGGLER_LIBS ${VRJ_LIB} )
ENDIF( ${VRJ_LIB} )

   
FIND_LIBRARY( VRJ_OGL_LIB, vrj_ogl
		          ${VJ_BASE_DIR}/lib64
		          ${VJ_BASE_DIR}/lib
		          /usr/local/lib64
		          /usr/local/lib )

IF( ${VRJ_OGL_LIB} )
  SET( VRJUGGLER_LIBS ${VRJUGGLER_LIBS} ${VRJ_OGL_LIB} )
ENDIF( ${VRJ_OGL_LIB} )


FIND_LIBRARY( VPR_LIB, vpr
		          ${VJ_BASE_DIR}/lib64
		          ${VJ_BASE_DIR}/lib
		          /usr/local/lib64
		          /usr/local/lib )

IF( ${VPR_LIB} )
  SET( VRJUGGLER_LIBS ${VRJUGGLER_LIBS) ${VPR_LIB} )
ENDIF( ${VRJ_LIB} )


FIND_LIBRARY( GADGET_LIB, gadget
		          ${VJ_BASE_DIR}/lib64
		          ${VJ_BASE_DIR}/lib
		          /usr/local/lib64
		          /usr/local/lib )

IF( ${GADGET_LIB} )
  SET( VRJUGGLER_LIBS ${VRJUGGLER_LIBS) ${GADGET_LIB} )
ENDIF( ${GADGET_LIB} )


FIND_LIBRARY( JCCL_LIB, jccl
		          ${VJ_BASE_DIR}/lib64
		          ${VJ_BASE_DIR}/lib
		          /usr/local/lib64
		          /usr/local/lib )

IF( ${JCCL_LIB} )
  SET( VRJUGGLER_LIBS ${VRJUGGLER_LIBS ${JCCL_LIB} )
ENDIF( ${JCCL_LIB} )


FIND_LIBRARY( TWEEK_LIB, tweek
		          ${VJ_BASE_DIR}/lib64
		          ${VJ_BASE_DIR}/lib
		          /usr/local/lib64
		          /usr/local/lib )

IF( ${TWEEK_LIB} )
  SET( VRJUGGLER_LIBS ${VRJUGGLER_LIBS} ${TWEEK_LIB} )
ENDIF( ${TWEEK_LIB} )


FIND_LIBRARY( SONIX_LIB, sonix
		          ${VJ_BASE_DIR}/lib64
		          ${VJ_BASE_DIR}/lib
		          /usr/local/lib64
		          /usr/local/lib )
		              
IF( ${SONIX_LIB} )
  SET( VRJUGGLER_LIBS ${VRJUGGLER_LIBS} ${SONIX_LIB} )
ENDIF( ${SONIX_LIB} )

