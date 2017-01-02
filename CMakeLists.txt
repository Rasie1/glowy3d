cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++14 -g -Wall -Wextra)

project(glowy3d)


find_package(OpenGL REQUIRED)

include_directories(include)
file(GLOB_RECURSE SRC_LIST src *.cpp)

add_library(glowy3d ${SRC_LIST})

add_subdirectory(test)

enable_testing()
