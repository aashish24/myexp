cmake_minimum_required(VERSION 2.8.2)

project(test1)

find_path(OGR_INC ogr_api.h
          /home/aashish/tools/gdal/trunk
          $ENV{GDAL_ROOT}
)

find_library(GDAL_LIB gdal
             /home/aashish/tools/gdal
             $ENV{GDAL_ROOT}
)

include_directories(${OGR_INC})

set(SRCS main.cxx)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} ${GDAL_LIB})
