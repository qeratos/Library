cmake_minimum_required(VERSION 3.17)
project(library)

set(CMAKE_CXX_STANDARD 20)

add_executable(library main.cpp logic.h database.h)