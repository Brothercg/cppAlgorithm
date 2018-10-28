cmake_minimum_required(VERSION 3.8)
project(cppAlgorithm)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SortTestHelper.h Student.h)
add_executable(cppAlgorithm ${SOURCE_FILES})