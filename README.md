# glowy3d

This is a framework for creating 3d applications made for educational purposes (working environment for computer graphics course in Southern Federal University).  

It has c++14 binding for common opengl conceptions and considered to be easy to use.

It is a fork of [glowy2d](https://github.com/Rasie1/glowy2d/) engine previously made by me in 2014.

## Dependencies

- boost
- cpptoml
- OpenGL, GLEW, glfw3
- zlib, libpng
- tinyobjloader

## How to build

```
mkdir build
cd build
cmake ..
make -j4
```

## Examples

There are 2 examples.

- **Triangle example**. Unfortunately, with no triange (because it's work in progress), only black screen
- **Simple platformer**. This one works.

To get an example working, you should copy contents of corresponding directory in `res/test` directory to the same place where output binary is located. For example, after you `make` the project, copy everything from `res/test/SamplePlatformer` to `build/test/SamplePlatformer` and run `sampleplatformer`.
