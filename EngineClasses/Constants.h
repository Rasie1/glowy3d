/****************************************************************************
This file is part of glowy2d.

Copyright (c) 2014 Kvachev 'Rasie1' V. D.

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
#include "IncludesEngine.h"
#include "ConstantsTriangleList.h"

#define SCREEN_HATE 768
#define SCREEN_WEED 1024
#define MOUSE_SPEED 0.5f
#define MOVE_SPEED 1.0f
#define ZOOM_SPEED 1.0f
#define DRAWING_TYPE_STATIC GL_STATIC_DRAW
#define DRAWING_TYPE_DYNAMIC GL_DYNAMIC_DRAW
#define SPRITES_PER_LAYER_LIMIT 10922

namespace glowy2d
{

	namespace Constants
	{
		enum BlendingModes
		{
			Replace,
			Screen,
			Multiply
		};

		const float texCoords[] = {
			0.f, 1.f,
			0.f, 0.f,
			1.f, 1.f,
			1.f, 0.f,
		};
		
		const float quadCoords[] = {
			0.f, 1.f, 0.f,
			0.f, 0.f, 0.f,
			1.f, 1.f, 0.f,
			1.f, 0.f, 0.f,
		};


		//const unsigned quadIndices[] = 
		//{ 0, 1, 2, 3, 2, 1 };


		const int antialiasing = 16;

		//Sets FPS limit. 0 disables V-Sync
		const int maxFPS = 0;

	}
}

