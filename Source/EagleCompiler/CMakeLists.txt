cmake_minimum_required(VERSION 2.8)

project(EagleCompiler)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY, cmake_obj)

add_subdirectory(scanner)
add_subdirectory(parser)
add_subdirectory(assemblizer)

add_executable(EagleCompiler main.cpp)