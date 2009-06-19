
cmake_minimum_required(VERSION "2.6")

PROJECT (CadKit)

# Set variables needed below...
SET ( CADKIT_INC_DIR ${PROJECT_SOURCE_DIR} )
SET ( CMakeModules "${PROJECT_SOURCE_DIR}/CMakeModules")

# Path to look for .cmake files.
SET( CMAKE_MODULE_PATH ${CMakeModules} )

INCLUDE ( Cadkit )

#########################################################
#
#  Set some Apple specific properties.
#
#########################################################

IF (APPLE)
	
	option(OSX_DWARF_DEBUG "Use Dwarf Debug Style" ON)
	IF (OSX_DWARF_DEBUG )
		SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-2")
	ENDIF(OSX_DWARF_DEBUG )

	# CMake doesn't define _DEBUG when using Xcode.
	IF(${CMAKE_GENERATOR} MATCHES "Xcode")
		SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG" )
	ENDIF(${CMAKE_GENERATOR} MATCHES "Xcode")
	
ENDIF (APPLE)


#########################################################
#
#  Find boost.
#
#########################################################

FIND_LIBRARY ( Boost_FILESYSTEM_LIBRARY_DEBUG      libboost_filesystem-mt-d.so
$ENV{BOOST_LIB_DIR} )
FIND_LIBRARY ( Boost_SYSTEM_LIBRARY_DEBUG          libboost_system-mt-d.so
$ENV{BOOST_LIB_DIR} )

IF( Boost_FILESYSTEM_LIBRARY_DEBUG )
	SET( Boost_SYSTEM_LIBRARY Boost_SYSTEM_LIBRARY_DEBUG )
 #SET( Boost_FILESYSTEM_LIBRARY_DEBUG )
  #SET( Boost_FILESYSTEM_LIBRARY Boost_FILESYSTEM_LIBRARY_DEBUG )
   message(STATUS "Found BOOST")
ENDIF( Boost_FILESYSTEM_LIBRARY_DEBUG )

   SET (FindBoost_DEBUG ON)
   SET ( BOOST_INCLUDEDIR $ENV{BOOST_INC_DIR} )
   SET ( BOOST_LIBRARYDIR $ENV{BOOST_LIB_DIR} )
   #FIND_PACKAGE( Boost 1.36 COMPONENTS date_time filesystem regex
   #threads system )


#SET ( BOOST_INCLUDEDIR $ENV{BOOST_INC_DIR} )
#SET ( BOOST_LIBRARYDIR $ENV{BOOST_LIB_DIR} )
#FIND_PACKAGE( Boost 1.36 COMPONENTS date_time filesystem regex threads system )

ADD_SUBDIRECTORY ( Helios )

OPTION ( BUILD_CADKIT_TESTS "Build CadKit test programs."  OFF )

IF ( BUILD_CADKIT_TESTS )
	ADD_SUBDIRECTORY ( Tests )
ENDIF ( BUILD_CADKIT_TESTS )
