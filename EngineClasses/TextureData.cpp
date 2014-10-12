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
#include "TextureData.h"
#include "EngineDirector.h"

namespace glowy2d
{
	TextureData * TextureData::load(const char * imagePath)
	{

		// Data read from the header of the BMP file
		unsigned char header[54]; // Each BMP file begins by a 54-bytes header
		unsigned int dataPos;     // Position in the file where the actual data begins
		usvec2 size;
		unsigned int imageSize;   // = width*height*3
		// Actual RGB data
		unsigned char * data;

		// Open the file
		FILE * file = fopen(imagePath, "rb");
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

		auto ret = new TextureData(size, data);

		return ret;
	}

	TextureData * TextureData::textureDataWithColor(usvec2 size, ucvec4 rgba)
	{
		unsigned char * data = new unsigned char[size.x * size.y * 3];

		//fill data
		for (int i = size.x * size.y * 3 - 1; i >= 0; i -= 3)
		{
			data[i] = rgba.b;
			data[i - 1] = rgba.g;
			data[i - 2] = rgba.r;
		}
		return new TextureData(size, data);
	}

	TextureData::~TextureData()
	{
		delete[] data;
	}
}