/****************************************************************************
This file is part of glowy2d.

Copyright (c) 2015 Kvachev 'Rasie1' V. D.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#pragma once
//Precompiled headers file

//STD includes
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <functional>
#include <vector>
#include <stdexcept>
#include <string>

#ifdef R_OGL
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#endif

#ifdef R_D3D
#pragma comment(lib, "DirectXTex.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")

#include <d3d11.h>
#include <d3d11shader.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <dinput.h>
#include <windows.h>
#endif

//glowy2d includes
#include "g2dMath.h"
#include "Math/rect.h"
#include "Base/System.h"

using namespace std;
using namespace glm;