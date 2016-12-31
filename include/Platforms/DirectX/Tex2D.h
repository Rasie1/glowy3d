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
#ifdef R_D3D
#include "g2dMath.h"

struct ID3D11Texture2D;
struct ID3D11ShaderResourceView;
struct ID3D11SamplerState;

namespace glowy2d
{

class TextureData;

struct Tex2D
{
public:	
	Tex2D(TextureData * data);
	Tex2D(const char * filename);
	Tex2D() {}
	~Tex2D();

	void bind();

	//Modifies texture data by replacing selected pixels
	void pixelsReplace(TextureData * data, usvec2 offset);

	static Tex2D load(const ubyte * data, const usvec2& size);

	//Deletes the texture from memory
	void release();

private:
	ID3D11Texture2D 		 * texture = nullptr;
	ID3D11ShaderResourceView * textureView;
	ID3D11SamplerState 		 * textureSamplerState;

	usvec2 size;
};

}
#endif