
SET( CPPDOM_LIB_DIR $ENV{CPPDOM_LIB_DIR} )

FIND_PATH( CPPDOM_INC_DIR cppdom/cppdom.h 
           $ENV{CPPDOM_INC_DIR}/*
            /usr/local/include/* )
                
FIND_LIBRARY( CPPDOM_LIB cppdom
              ${CPPDOM_LIB_DIR}
              /usr/local/lib64
              /usr/local/lib )
              