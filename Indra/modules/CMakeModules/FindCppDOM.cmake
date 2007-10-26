
SET( CPPDOM_LIB_DIR $ENV{CPPDOM_LIB_DIR} )

FIND_PATH( CPPDOM_INC_DIR cppdom/cppdom.h 
           $ENV{CPPDOM_INC_DIR}/*
           /usr/local/include/* )
                
FIND_LIBRARY( CPPDOM_LIB 
	      NAMES cppdom-0_7_8
	            cppdom-0_7_9
		    cppdom-0_7_10
		    cppdom-0_8_1
		    cppdom-0_8_2
              PATHS ${CPPDOM_LIB_DIR}
                    /usr/local/lib64
                    /usr/local/lib )
              