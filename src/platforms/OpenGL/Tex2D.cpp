/****************************************************************************
This file is part of glowy3d.

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
#include "epc.h"
#ifdef R_OGL
#include "Base/System.h"
#include "Graphics/TextureData.h"
#include "Platforms/Tex2D.h"
#include "Platforms/Renderer.h"

using namespace std;
using namespace glm;

namespace glowy3d
{

Tex2D::Tex2D(TextureData * data) :
	size(data->resolution)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	
	glTexImage2D(GL_TEXTURE_2D, 
				 0, 
				 GL_RGBA, 
				 size.x, 
				 size.y, 0, 
				 GL_RGBA, 
				 GL_UNSIGNED_BYTE, 
				 data->data);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	/*glGenerateMipmap(GL_TEXTURE_2D);*/
}

void Tex2D::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

Tex2D::Tex2D(const char * filename) : Tex2D(TextureData::load(filename))
{
}

Tex2D::~Tex2D()
{
}

void Tex2D::release()
{
	glDeleteTextures(1, &id);
}

void Tex2D::pixelsReplace(TextureData * data, usvec2 offset)
{
	bind();
	glTexSubImage2D(GL_TEXTURE_2D, 0, offset.x, offset.y, data->resolution.x, data->resolution.y, GL_RGBA, GL_UNSIGNED_BYTE, data->data);
	//glGenerateMipmap(GL_TEXTURE_2D);
}

}
#endif
