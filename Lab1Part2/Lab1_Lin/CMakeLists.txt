cmake_minimum_required(VERSION 3.23)
project(Lab1_Lin)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab1_Lin main.cpp)

add_library(num
        ../num/cmake-build-debug/libnum.a
        ../num/library.cpp)

add_library(vec
        ../vec/cmake-build-debug/libvec.so
        ../vec/vec.cpp)

target_link_libraries(Lab1_Lin PUBLIC num vec)