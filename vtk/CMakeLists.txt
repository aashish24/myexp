# VTK is required.
find_package(VTK REQUIRED)
if(VTK_FOUND)
  include(${VTK_USE_FILE})
else(VTK_FOUND)
  message(FATAL_ERROR, "VTK is required")
endif(VTK_FOUND)

#add_subdirectory(vtkgis)
#add_subdirectory(vtk3ds)
#add_subdirectory(vtk-android)
