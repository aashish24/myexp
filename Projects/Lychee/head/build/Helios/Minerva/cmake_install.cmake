# Install script for directory: /store/home/aashish/src/cadkit/head/build/Minerva

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/store/home/aashish/src/cadkit/head/install/x86_64.gcc-4_1_2.debug")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Minerva/Core/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Minerva/Kml/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Minerva/GeoNames/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Minerva/Document/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Minerva/Widgets/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Minerva/Application/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Minerva/GeoRSS/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Minerva/DataSources/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Minerva/PG/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Minerva/PostGIS/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Minerva/GDAL/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Minerva/OSSIM/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Minerva/Plugins/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

