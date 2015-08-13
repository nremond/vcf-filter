cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(vcfFilterProject)

enable_testing()

add_subdirectory(main)
add_subdirectory(test)
add_subdirectory(libvcf)
