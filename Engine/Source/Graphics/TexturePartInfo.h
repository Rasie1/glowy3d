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
#include <string>
#include "glm/glm.hpp"
#include "Math/AdditionGLM.h"
#include "Math/AdditionGLMrect.h"

//TODO
//-add colors, hsb, shaders, rotation

namespace glowy2d
{
	class TexturePartInfo
	{
	public:
		//This class represent an info about part of TextureInfo
		//such as texture image path, shader, position, color, etc
		TexturePartInfo(const std::string& path, const rect& rectangle = rect(vec2(0.f, 0.f), vec2(1.f, 1.f)));
		~TexturePartInfo();

		const std::string& getPath() const;
		void setPath(const std::string& newPath);
		
		const rect& getRect() const;
		void setRect(const rect& newRect);

	private:
		rect rectangle;
		std::string path;
	};
}