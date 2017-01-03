find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories (${TEST_SOURCE_DIR}) 

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) 

file(GLOB_RECURSE SAMPLE_PLATFORMER_SRC *.cpp)
file(GLOB_RECURSE SAMPLE_PLATFORMER_RES ../../res/SamplePlatformer/*)

add_executable (sampleplatformer ${SAMPLE_PLATFORMER_SRC} ${TEST_SOURCE_DIR}) 

target_link_libraries(sampleplatformer
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      glowy3d
                      glfw3
                      m rt
                      GL GLU
                      X11 Xxf86vm Xrandr Xi Xinerama Xcursor
                      pthread
                      dl
                      GLEW
                      png
                      )

enable_testing()
add_test(glowy3d sampleplatformer)
