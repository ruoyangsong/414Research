cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(mesh_volume)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (mesh_volume mesh_volume.cpp)
target_link_libraries (mesh_volume ${PCL_LIBRARIES})
