cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(poisson_reconstruction)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (poisson_reconstruction poisson_reconstruction.cpp)
target_link_libraries (poisson_reconstruction ${PCL_LIBRARIES})
