cmake_minimum_required(VERSION 3.1)
add_definitions(
-std=c++11 
-DR_OGL
-g
)

project(glowy2d)

file(GLOB_RECURSE g2d_SOURCES "src/*.cpp")
file(GLOB_RECURSE g2d_HEADERS "inc/*.h")

set (g2d_INCLUDE_DIRS "inc")
foreach (_headerFile ${g2d_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND g2d_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES g2d_INCLUDE_DIRS)

include_directories(${g2d_INCLUDE_DIRS})
#add_executable (glowy2d ${g2d_SOURCES})

ADD_LIBRARY(Glowy2D STATIC ${g2d_SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/dep/glm)
include_directories(${CMAKE_SOURCE_DIR}/dep/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/dep/glew/include)
include_directories(${CMAKE_SOURCE_DIR}/dep/lpng)
include_directories(${CMAKE_SOURCE_DIR}/dep/zlib)

message(STATUS "CMAKE_GENERATOR : ${CMAKE_GENERATOR}")
message(STATUS "FILELIST        : ${FILELIST}")
message(STATUS "SYSTEM_NAME     : ${CMAKE_SYSTEM_NAME}")