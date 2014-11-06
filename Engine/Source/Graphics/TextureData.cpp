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
#include "epc.h"
#include "Graphics/TextureData.h"
#include "Base/EngineDirector.h"
#include "png.h"

#define TEXTURE_LOAD_ERROR 0


namespace glowy2d
{
	TextureData * TextureData::load(const char * imagePath)
	{
		usvec2 size;
		//header for testing if it is a png
		png_byte header[8];

		//open file as binary
		FILE *fp = fopen(imagePath, "rb");
		if (!fp) {
			throw runtime_error("Can't open image file\n");
			return 0;
		}

		//read the header
		fread(header, 1, 8, fp);

		//test if png
		int is_png = !png_sig_cmp(header, 0, 8);
		if (!is_png) {
			fclose(fp);
			throw runtime_error("Can't load png image file\n");
			return TEXTURE_LOAD_ERROR;
		}

		//create png struct
		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
			NULL, NULL);
		if (!png_ptr) {
			fclose(fp);
			throw runtime_error("Can't load png image file\n");
			return (TEXTURE_LOAD_ERROR);
		}

		//create png info struct
		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr) {
			png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
			fclose(fp);
			throw runtime_error("Can't load png image file\n");
			return (TEXTURE_LOAD_ERROR);
		}

		//create png info struct
		png_infop end_info = png_create_info_struct(png_ptr);
		if (!end_info) {
			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
			fclose(fp);
			throw runtime_error("Can't load png image file\n");
			return (TEXTURE_LOAD_ERROR);
		}

		//png error stuff, not sure libpng man suggests this.
		if (setjmp(png_jmpbuf(png_ptr))) {
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			fclose(fp);
			throw runtime_error("Can't load png image file\n");
			return (TEXTURE_LOAD_ERROR);
		}

		//init png reading
		png_init_io(png_ptr, fp);

		//let libpng know you already read the first 8 bytes
		png_set_sig_bytes(png_ptr, 8);

		// read all the info up to the image data
		png_read_info(png_ptr, info_ptr);

		//variables to pass to get info
		int bit_depth, color_type;
		png_uint_32 twidth, theight;

		// get info about png
		png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type,
			NULL, NULL, NULL);

		//update width and height based on png info
		size.x = twidth;
		size.y = theight;

		// Update the png info struct.
		png_read_update_info(png_ptr, info_ptr);

		// Row size in bytes.
		int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

		// Allocate the image_data as a big block, to be given to opengl
		png_byte *data = new png_byte[rowbytes * theight];
		if (!data) {
			//clean up memory and close stuff
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			fclose(fp);
			throw runtime_error("Can't load png image file\n");
			return TEXTURE_LOAD_ERROR;
		}

		//row_pointers is for pointing to image_data for reading the png with libpng
		png_bytep *row_pointers = new png_bytep[theight];
		if (!row_pointers) {
			//clean up memory and close stuff
			png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
			delete[] data;
			fclose(fp);
			throw runtime_error("Can't load png image file\n");
			return TEXTURE_LOAD_ERROR;
		}
		// set the individual row_pointers to point at the correct offsets of image_data
		for (uint i = 0; i < theight; ++i)
			row_pointers[theight - 1 - i] = data + i * rowbytes;

		//read the png into image_data through row_pointers
		png_read_image(png_ptr, row_pointers);

		//clean up memory and close stuff
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		delete[] row_pointers;
		fclose(fp);

		/*
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
		*/
		auto ret = new TextureData(size, data);

		return ret;
	}

	TextureData * TextureData::textureDataWithColor(usvec2 size, ucvec4 rgba)
	{
		unsigned char * data = new unsigned char[size.x * size.y * 4];

		//fill data
		for (int i = size.x * size.y * 4 - 1; i >= 0; i -= 4)
		{
			data[i] = rgba.a;
			data[i - 1] = rgba.b;
			data[i - 2] = rgba.g;
			data[i - 3] = rgba.r;
		}
		return new TextureData(size, data);
	}

	TextureData::~TextureData()
	{
		delete[] data;
	}

	void TextureData::modify(TextureData * data, const usvec2& offset, std::function<void(ubyte*, ubyte*)> blendFunction)
	{
		//not fastest copy code
		uint16 i, j, row;
		for (i = 0; i < data->size.y; ++i)
		{
			row = i + offset.y;
			for (j = 0; j < data->size.x; ++j)
			{
				blendFunction(
					&(this->data[4 * (size.x * row + j + offset.x)]),
					&(data->data[4 * (data->size.x * i + j)]));
			}
		}
	}
}