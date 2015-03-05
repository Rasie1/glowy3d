cmake_minimum_required(VERSION 3.1)
add_definitions(
    -std=c++11
    -DR_OGL
    -g
    )

project(glowy2d_game)

file(GLOB_RECURSE g2d_SOURCES "SourceSamplePlatformer/*.cpp")
file(GLOB_RECURSE g2d_HEADERS "SourceSamplePlatformer/*.h")

set (g2d_INCLUDE_DIRS "SourceSamplePlatformer")
foreach (_headerFile ${g2d_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND g2d_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES g2d_INCLUDE_DIRS)

include_directories(${g2d_INCLUDE_DIRS})
add_executable (glowy2d_game ${g2d_SOURCES})

#ADD_LIBRARY(Glowy2D STATIC ${g2d_SOURCES})

#TARGET_LINK_LIBRARIES( MyLibraryName  ITKCommon )

include_directories(${CMAKE_SOURCE_DIR}/Glowy2D/inc)
target_link_libraries(glowy2d_game ${CMAKE_SOURCE_DIR}/Glowy2D/lib/libGlowy2D.a)

include_directories(${CMAKE_SOURCE_DIR}/Glowy2D/dep/glm)
include_directories(${CMAKE_SOURCE_DIR}/Glowy2D/dep/glew/include)
target_link_libraries(glowy2d_game ${CMAKE_SOURCE_DIR}/Glowy2D/dep/glew/lib/libglew32.dll.a)
include_directories(${CMAKE_SOURCE_DIR}/Glowy2D/dep/glfw/include)
target_link_libraries(glowy2d_game ${CMAKE_SOURCE_DIR}/Glowy2D/dep/glfw/lib/libglfw3.a)
target_link_libraries(
       glowy2d_game
       Opengl32.lib                                   
       ws2_32.lib
       psapi.lib
       iphlpapi.lib
       )

include_directories(${CMAKE_SOURCE_DIR}/Glowy2D/dep/lpng)
target_link_libraries(glowy2d_game ${CMAKE_SOURCE_DIR}/Glowy2D/dep/lpng/libpng16.lib)
include_directories(${CMAKE_SOURCE_DIR}/Glowy2D/dep/zlib)
target_link_libraries(glowy2d_game ${CMAKE_SOURCE_DIR}/Glowy2D/dep/zlib/zlib.lib)


message(STATUS "CMAKE_GENERATOR : ${CMAKE_GENERATOR}")
message(STATUS "FILELIST        : ${FILELIST}")
message(STATUS "SYSTEM_NAME     : ${CMAKE_SYSTEM_NAME}")