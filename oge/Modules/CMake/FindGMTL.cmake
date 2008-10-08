
SET( GMTL_INC $ENV{GMTL_INC_DIR} )


FIND_PATH( GMTL_INC_DIR gmtl/gmtl.h 
           ${GMTL_INC}
           ${GMTL_INC}/*
           /usr/local/include/* )
               
              
