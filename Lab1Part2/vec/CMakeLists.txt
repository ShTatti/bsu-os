cmake_minimum_required(VERSION 3.23)
project(vec)

set(CMAKE_CXX_STANDARD 14)

add_library(num
        ../num/cmake-build-debug/libnum.a
        ../num/library.cpp)

add_library(vec SHARED vec.cpp vec.h)