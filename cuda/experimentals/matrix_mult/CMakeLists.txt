cmake_minimum_required(VERSION 2.8.2 FATAL_ERROR)

find_package(CUDA REQUIRED)

cuda_add_executable(matrix_mult matrix_mult.cu main.cpp)
