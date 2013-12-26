project(checkext)
cmake_minimum_required(VERSION 2.8)
find_package(VTK REQUIRED NO_MODULE)
include(${VTK_USE_FILE})
set(SRC_LIST main.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})

