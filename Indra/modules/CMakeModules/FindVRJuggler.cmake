
SET( VJ_INC_DIR  $ENV{VJ_BASE_DIR}/include )
SET( VJ_BASE_DIR $ENV{VJ_BASE_DIR} )


FIND_PATH( VRJUGGLER_VRJ_INC vrj/vrjConfig.h
           ${VJ_INC_DIR}/*
	   /usr/local/include/* )

IF( VRJUGGLER_VRJ_INC )
 SET( VRJUGGLER_INCS ${VRJUGGLER_VRJ_INC} )
ENDIF( VRJUGGLER_VRJ_INC )
	   
	   
FIND_LIBRARY( VRJUGGLER_VRJ_LIB 		 
	      NAMES vrj-2_0
	      	    vrj-2_1
	            vrj-2_2
	            vrj-2_3
	            vrj-2_4
	            vrj-3_0
	            vrj-3_1
	            vrj-3_2
	            vrj-3_3
	            vrj-3_4
	      PATHS ${VJ_BASE_DIR}/lib64
	            ${VJ_BASE_DIR}/lib
	            /usr/local/lib64
	            /usr/local/lib )
		     
IF( VRJUGGLER_VRJ_LIB )
  SET( VRJUGGLER_LIBS ${VRJUGGLER_VRJ_LIB} )  
ENDIF( VRJUGGLER_VRJ_LIB )

  
FIND_LIBRARY( VRJUGGLER_VRJ_OGL_LIB
              NAMES vrj_ogl-2_0
	      	    vrj_ogl-2_1
		    vrj_ogl-2_2
		    vrj_ogl-2_3
		    vrj_ogl-2_4
		    vrj_ogl-3_0
		    vrj_ogl-3_1
		    vrj_ogl-3_2
		    vrj_ogl-3_3
		    vrj_ogl-3_4
             PATHS  ${VJ_BASE_DIR}/lib64
	            ${VJ_BASE_DIR}/lib
	            /usr/local/lib64
	            /usr/local/lib )

IF( VRJUGGLER_VRJ_OGL_LIB )
  SET( VRJUGGLER_LIBS ${VRJUGGLER_LIBS} ${VRJUGGLER_VRJ_OGL_LIB} )
ENDIF( VRJUGGLER_VRJ_OGL_LIB )


FIND_PATH( VRJUGGLER_VPR_INC vpr/vprConfig.h
           ${VJ_INC_DIR}/*
	   /usr/local/include/* )

IF( VRJUGGLER_VPR_INC )
 SET( VRJUGGLER_INCS ${VRJUGGLER_INCS} ${VRJUGGLER_VPR_INC} )
ENDIF( VRJUGGLER_VPR_INC )


FIND_LIBRARY( VRJUGGLER_VPR_LIB
	      NAMES vpr-2_0
	      	    vpr-2_1
		    vpr-2_2
		    vpr-2_3
		    vpr-2_4
		    vpr-3_0
		    vpr-3_1
		    vpr-3_2
		    vpr-3_3
		    vpr-3_4	      
	      PATHS ${VJ_BASE_DIR}/lib64
	            ${VJ_BASE_DIR}/lib
	            /usr/local/lib64
	            /usr/local/lib )

IF( VRJUGGLER_VPR_LIB )
  SET( VRJUGGLER_LIBS ${VRJUGGLER_LIBS} ${VRJUGGLER_VPR_LIB} )
ENDIF( VRJUGGLER_VPR_LIB )


FIND_PATH( VRJUGGLER_GADGET_INC gadget/gadgetConfig.h
           ${VJ_INC_DIR}/*
	   /usr/local/include/* )

IF( VRJUGGLER_GADGET_INC )
 SET( VRJUGGLER_INCS ${VRJUGGLER_INCS} ${VRJUGGLER_GADGET_INC} )
ENDIF( VRJUGGLER_GADGET_INC )


FIND_LIBRARY( VRJUGGLER_GADGET_LIB
	      NAMES gadget-1_0
	      	    gadget-1_1
		    gadget-1_2
		    gadget-1_3
		    gadget-1_4
		    gadget-2_0
		    gadget-2_1
		    gadget-2_2
		    gadget-2_3
		    gadget-2_4
	      PATHS ${VJ_BASE_DIR}/lib64
	            ${VJ_BASE_DIR}/lib
	            /usr/local/lib64
	            /usr/local/lib )

IF( ${VRJUGGLER_GADGET_LIB} )
  SET( VRJUGGLER_LIBS ${VRJUGGLER_LIBS} ${VRJUGGLER_GADGET_LIB} )
ENDIF( ${VRJUGGLER_GADGET_LIB} )


FIND_PATH( VRJUGGLER_JCCL_INC jccl/jcclConfig.h
           ${VJ_INC_DIR}/*
	   /usr/local/include/* )

IF( VRJUGGLER_JCCL_INC )
 SET( VRJUGGLER_INCS ${VRJUGGLER_INCS} ${VRJUGGLER_JCCL_INC} )
ENDIF( VRJUGGLER_JCCL_INC )


FIND_LIBRARY( VRJUGGLER_JCCL_LIB
              NAMES jccl-1_0
	            jccl-1_1
		    jccl-1_2
		    jccl-1_3
		    jccl-1_4
		    jccl-2_0
		    jccl-2_1
		    jccl-2_2
		    jccl-2_3
		    jccl-2_4
             PATHS  ${VJ_BASE_DIR}/lib64
		    ${VJ_BASE_DIR}/lib
		    /usr/local/lib64
		    /usr/local/lib )

IF( VRJUGGLER_JCCL_LIB )
  SET( VRJUGGLER_LIBS ${VRJUGGLER_LIBS} ${VRJUGGLER_JCCL_LIB} )
ENDIF( VRJUGGLER_JCCL_LIB )


FIND_PATH( VRJUGGLER_TWEEK_INC tweek/tweekConfig.h
           ${VJ_INC_DIR}/*
	   /usr/local/include/* )

IF( VRJUGGLER_TWEEK_INC )
 SET( VRJUGGLER_INCS ${VRJUGGLER_INCS} ${VRJUGGLER_TWEEK_INC} )
ENDIF( VRJUGGLER_TWEEK_INC )


FIND_LIBRARY( VRJUGGLER_TWEEK_LIB 
              NAMES tweek-1_0
		    tweek-1_1
		    tweek-1_2
		    tweek-1_3
		    tweek-1_4
		    tweek-2_0
		    tweek-2_1
		    tweek-2_2
		    tweek-2_3
		    tweek-2_4
	      PATHS ${VJ_BASE_DIR}/lib64
		    ${VJ_BASE_DIR}/lib
		    /usr/local/lib64
		    /usr/local/lib )

IF( ${VRJUGGLER_TWEEK_LIB} )
  SET( VRJUGGLER_LIBS ${VRJUGGLER_LIBS} ${VRJUGGLER_TWEEK_LIB} )
ENDIF( ${VRJUGGLER_TWEEK_LIB} )


FIND_PATH( VRJUGGLER_SONIX_INC snx/snxConfig.h
           ${VJ_INC_DIR}/*
	   /usr/local/include/* )

IF( VRJUGGLER_SONIX_INC )
 SET( VRJUGGLER_INCS ${VRJUGGLER_INCS} ${VRJUGGLER_SONIX_INC} )
ENDIF( VRJUGGLER_SONIX_INC )


FIND_LIBRARY( VRJUGGLER_SONIX_LIB 
              NAMES sonix-1_0
		    sonix-1_1
		    sonix-1_2
		    sonix-1_3
		    sonix-1_4
		    sonix-2_0
		    sonix-2_1
		    sonix-2_2
		    sonix-2_3
		    sonix-2_4
	      PATHS ${VJ_BASE_DIR}/lib64
		    ${VJ_BASE_DIR}/lib
		    /usr/local/lib64
		    /usr/local/lib )

IF( VRJUGGLER_SONIX_LIB )
  SET( VRJUGGLER_LIBS ${VRJUGGLER_LIBS} ${VRJUGGLER_SONIX_LIB} )
ENDIF( VRJUGGLER_SONIX_LIB )
