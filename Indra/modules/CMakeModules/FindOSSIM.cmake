
#------Set ossim include and library paths.
FIND_PATH( OSSIM_INC_DIR $ENV{OSSIM_INC_DIR} )


FIND_LIBRARY( OSSIM_LIB ossim $ENV{OSSIM_LIB_DIR} )


#------Set ossimPlanet include and library paths.
FIND_PATH( OSSIMPLANET_INC_DIR $ENV{OSSIMPLANET_INC_DIR} )


FIND_LIBRARY( OSSIMPLANET_LIB ossimPlanet ${OSSIMPLANET_LIB_DIR} )


