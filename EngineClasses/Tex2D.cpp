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
#include "stdafx.h"
#include "Tex2D.h"
#include "EngineDirector.h"

namespace glowy2d
{
	Tex2D::Tex2D(TextureData * data)
	{
		size = data->size;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);


		bool mipmaps = false;

		if (mipmaps)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_BGR, GL_UNSIGNED_BYTE, data->data);

		if (mipmaps)
			glGenerateMipmap(GL_TEXTURE_2D);

	}

	void Tex2D::bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, id);
		//glTexSubImage2D(GL_TEXTURE_2D, 0, offx, offy, x, x, GL_BGR, GL_UNSIGNED_BYTE, pixels);
		//uniform_id = glGetUniformLocation(EngineDirector::getInstance()->program_id, "mytexture");
		//glUniform1i(uniform_id, 0);
	}

	Tex2D::Tex2D(const char * filename) : /*Tex2D(Tex2D::loadBmp(filename))/*/Tex2D(Tex2D(TextureData::load(filename)))//*/
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
		glTexSubImage2D(GL_TEXTURE_2D, 0, offset.x, offset.y, data->size.x, data->size.y, GL_BGR, GL_UNSIGNED_BYTE, data->data);
	}

	void Tex2D::pixelsReplaceInBuffer(TextureData * data, usvec2 offset)
	{
		//bind();
		//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, data.size.x, data.size.y, GL_BGR, GL_UNSIGNED_BYTE, data.data);
	}

	void Tex2D::pixelsScreen(TextureData * data, usvec2 offset)
	{
		//bind();
		//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, data.size.x, data.size.y, GL_BGR, GL_UNSIGNED_BYTE, data.data);
	}

	void Tex2D::pixelsMultiply(TextureData * data, usvec2 offset)
	{
		//bind();
		//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, data.size.x, data.size.y, GL_BGR, GL_UNSIGNED_BYTE, data.data);
	}



	Tex2D Tex2D::loadBmp(const char * filename)
	{

		// Data read from the header of the BMP file
		unsigned char header[54]; // Each BMP file begins by a 54-bytes header
		unsigned int dataPos;     // Position in the file where the actual data begins
		usvec2 size;
		unsigned int imageSize;   // = width*height*3
		// Actual RGB data
		unsigned char * data;

		// Open the file
		FILE * file = fopen(filename, "rb");
		if (!file)
		{
			printf("Image could not be opened\n");
		}
		if (fread(header, 1, 54, file) != 54){ // If not 54 bytes read : problem
			printf("Not a correct BMP file\n");
		}
		if (header[0] != 'B' || header[1] != 'M'){
			printf("Not a correct BMP file\n");
		}

		// Read ints from the byte array
		dataPos = *(int*)&(header[0x0A]);
		imageSize = *(int*)&(header[0x22]);
		size.x = *(int*)&(header[0x12]);
		size.y = *(int*)&(header[0x16]);

		// Some BMP files are misformatted, guess missing information
		if (imageSize == 0)    imageSize = size.x * size.y * 3; // 3 : one byte for each Red, Green and Blue component
		if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

		// Create a buffer
		data = new unsigned char[imageSize];

		// Read the actual data from the file into the buffer
		fread(data, 1, imageSize, file);

		//Everything is in memory now, the file can be closed
		fclose(file);

		return Tex2D(new TextureData(size, data));
	}



}









