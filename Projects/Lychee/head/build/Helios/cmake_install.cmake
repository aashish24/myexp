# Install script for directory: /store/home/aashish/src/cadkit/head/build/Helios

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
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Usul/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/OpenThreads/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/OsgTools/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/XmlTree/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/XML/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/MenuKit/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/SceneModel/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/TriangleModel/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/VolumeModel/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/MatrixAnimation/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/PathAnimation/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/ModelPresentationLib/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/ModelPresentation/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/WrfModel/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/MeasureTool/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/CenterGeometry/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/EsriShapeFile/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/ModflowModel/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Minerva/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/Qt/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/PasswordPrompt/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/VRV/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/OSG/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/scene_operations/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/display_scene_stats/cmake_install.cmake")
  INCLUDE("/store/home/aashish/src/cadkit/head/build/Helios/CadViewer/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

