
SET( GMTL_INC_DIR $ENV{GMTL_INC_DIR} )


FIND_PATH( GMTL_INC_DIR gmtl/gmtl.h 
           ${GMTL_INC_DIR}/*
           /usr/local/include/* )
               
              
