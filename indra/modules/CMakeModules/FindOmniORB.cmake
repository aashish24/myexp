
SET( OMNIORB_INC_DIR $ENV{OMNIORB_INC_DIR} )
SET( OMNIORB_LIB_DIR $ENV{OMNIORB_LIB_DIR} )

FIND_LIBRARY( OMNITHREAD_LIB 
	      NAMES omnithread
              PATHS ${OMNIORB_LIB_DIR}
                    /usr/local/lib64
                    /usr/local/lib )


FIND_LIBRARY( OMNIDYNAMIC_LIB 
              NAMES omniDynamic4
              PATHS ${OMNIORB_LIB_DIR}
                    /usr/local/lib64
                    /usr/local/lib )
              

FIND_LIBRARY( OMNIORB_LIB  
              NAMES omniORB4
              PATHS ${OMNIORB_LIB_DIR}
                    /usr/local/lib64
                    /usr/local/lib )
