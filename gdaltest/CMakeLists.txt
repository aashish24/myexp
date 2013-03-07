cmake_minimum_required(VERSION 2.8.10)

project(gdaltest)
find_package(GDAL)

include_directories(${GDAL_INCLUDE_DIR})

set(srcs main.cxx)
add_executable(${PROJECT_NAME} ${srcs})

target_link_libraries(${PROJECT_NAME} ${GDAL_LIBRARY})
