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
#include "glm/glm.hpp"
#include "Math/AdditionGLM.h"
using glm::usvec2;

namespace glowy2d
{
	class Texture
	{
	public:
		//Class representing textures. Can be changed between 
		//Sprites in bounds of layer. Warning: you can't create
		//Textures by yourself, you must get them from Layer
		Texture();
		~Texture();

		friend class Layer;
		friend class TextureAtlas;
		friend class Sprite;
		
	private:
		//Copies coordinates from the source
		void copyFrom(const float * source);
		//Copies coordinates to the source
		void copyTo(float * destination);
		
		usvec2 size;
		float coords[8];
	};
}