# Install script for directory: /store/home/aashish/src/cadkit/head/build/Helios/Qt/Core

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" MATCHES "^(Unspecified)$")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/libHeliosQtCored.so")
    IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libHeliosQtCored.so")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libHeliosQtCored.so")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libHeliosQtCored.so")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" MATCHES "^(Unspecified)$")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" MATCHES "^(Unspecified)$")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/icons" TYPE FILE FILES
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/helios_sun.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/saveDocument.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/neg_x.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/smooth.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/no_triangle.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/floppy_small.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/lighting_on.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/neg_y.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/Top.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/play.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/forward_arrow_bar.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/neg_z.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/open.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/Bottom.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/SkipReverse.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/warning.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/VertexLight.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/keepconnected.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/triangle.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/points.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/FacetLight.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/hand.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/lines.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/copy.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/FastForward.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/plus_x.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/FrameDump.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/plus_y.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/writing.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/plus_z.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/Right.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/pause.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/AddTriangle.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/flat.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/BoundBox.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/home.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/Glass_Box.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/xyz.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/WireFrame.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/eye.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/backward_arrow.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/lightning.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/play_backwards.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/seek.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/Left.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/newDocument.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/SkipForward.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/camera.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/write.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/question.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/PlayReversesmall.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/cut.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/lighting_off.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/openDocument.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/Logo.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/PlayReverse.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/redx.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/delete.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/paste.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/stopsmall.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/forward_arrow.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/no_lightning.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/curve.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/stop.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/Rewind.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/Front.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/splash_screen.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/error.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/arrow.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/DeleteTriangle.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/info.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/playsmall.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/filled.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/Back.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/folder.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/lighting_two_sides_off.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/backward_arrow_bar.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/record.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/small_dot.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/id.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/lighting_two_sides_on.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/hidden_lines.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/print.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/deleteconnected.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/selection.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/Hidden.png"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/splash_screen.jpg"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/helios_installer_spash.jpg"
    "/store/home/aashish/src/cadkit/head/build/Helios/Qt/Core/../../Images/marble-3.jpg"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" MATCHES "^(Unspecified)$")

