#pragma once
#pragma message("Compiling precompiled headers.\n")

#define _CRT_SECURE_NO_WARNINGS
#define R_OPENGL
//#define R_DIRECT3D

//STD includes
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <functional>

//GL includes
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

//glowy2d includes
#include "Math/AdditionGLM.h"
#include "Math/AdditionGLMrect.h"
#include "Base/Constants.h"
#include "Graphics/Layer.h"
#include "Graphics/Sprite.h"
#include "Base/EngineDirector.h"

using glowy2d::Layer;
using glowy2d::Sprite;