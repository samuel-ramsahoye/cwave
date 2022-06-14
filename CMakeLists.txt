cmake_minimum_required(VERSION 3.4)
set(CMAKE_CC_COMPILER "/usr/bin/gcc-9")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-9")

project(pybind_vid)
add_subdirectory(pybind11)
pybind11_add_module(module_name main.cpp)
