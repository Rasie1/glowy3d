/****************************************************************************
This file is part of glowy3d.

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
#include <functional>
#include <algorithm>
#include <cstring>
#include "g2dMath.h"

namespace glowy3d
{

class TextureData
{
public:
	TextureData(usvec2 textureSize, ubyte * dataArray);
	~TextureData();

	ubyte * data;
	usvec2  resolution;
	int		bitDepth;
	int		colorType;
	glm::uint8 gap = 0;

	static TextureData * load(const char * imagePath);
	void				 save(const char * imagePath);
	static TextureData * textureDataWithColor(usvec2 size, ucvec4 rgba);

	//Modify data
	void modify(TextureData * data, const usvec2& offset, std::function<void(ubyte*, ubyte*)> blendFunction);
	//Removes edges when doing antialiased drawing
	void addGap(glm::uint8 gap);
};

//Blending functions for using with TextureData::modify
namespace BlendFunction
{
	inline void replace(ubyte * to, ubyte * from)
	{
		memcpy(to, from, 4);
	}

	inline void normal(ubyte * to, ubyte * from)
	{
		uint16 alpha = from[3] + 1;
		uint16 invAlpha = 256 - from[3];
		to[0] = ubyte((alpha * from[0] + invAlpha * to[0]) >> 8);
		to[1] = ubyte((alpha * from[1] + invAlpha * to[1]) >> 8);
		to[2] = ubyte((alpha * from[2] + invAlpha * to[2]) >> 8);
		to[3] = std::min(to[3] + from[3], 255);
	}

	inline void add(ubyte * to, ubyte * from)
	{
		*to += *from;
		*(to + 1) += *(from + 1);
		*(to + 2) += *(from + 2);
		*(to + 3) += *(from + 3);
	}

	inline void multiply(ubyte * to, ubyte * from)
	{
		//It's kind of wrong
		uint16 invAlpha = 256 - from[3];
		to[0] = ubyte((std::min(256, from[0] + from[0] * invAlpha) * to[0]) >> 8);
		to[1] = ubyte((std::min(256, from[1] + from[1] * invAlpha) * to[1]) >> 8);
		to[2] = ubyte((std::min(256, from[2] + from[2] * invAlpha) * to[2]) >> 8);
	}
}

}
