# Root cmake file.
cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)

project(test_globe)

# VTK is required.
find_package(VTK REQUIRED)
if(VTK_FOUND)
  include(${VTK_USE_FILE})
else(VTK_FOUND)
  message(FATAL_ERROR, "VTK is required")
endif(VTK_FOUND)

# Check if VTK is build with Qt support if yes
# use the configuration from VTK.
# or else find the Qt4 here.
if(VTK_USE_QVTK)
  include(${VTK_DIR}/VTKConfigQt.cmake)
else(VTK_USE_QVTK)
  message(FATAL_ERROR, "VTK with Qt is required")
endif(VTK_USE_QVTK)

find_package(Qt4)

if(NOT QT4_FOUND)
  message(FATAL_ERROR " QT not found")
endif(NOT QT4_FOUND)

include(${QT_USE_FILE})

set(SRCS main.cxx)

add_executable(test_globe ${SRCS})

target_link_libraries(test_globe
  ${QT_QTMAIN_LIBRARY} ${QT_LIBRARIES}
  QVTK
  vtkRendering
  vtkGeovis
)
