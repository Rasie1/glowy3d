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
#include "epc.h"
#include "Graphics/TextureData.h"
#include "Base/System.h"
#include "png.h"

namespace glowy2d
{

TextureData::TextureData(usvec2 textureSize, ubyte * dataArray) :
	resolution(textureSize),
	data(dataArray)
{
}

TextureData::~TextureData()
{
	delete[] data;
}

TextureData * TextureData::load(const char * imagePath)
{
	usvec2 size;
	//header for testing if it is a png
	png_byte header[8];

	//open file as binary
	FILE * file = fopen(imagePath, "rb");
	if (!file)
	{
		throw runtime_error("Can't open image file\n");
		return nullptr;
	}

	//read the header
	fread(header, 1, 8, file);

	//test if png
	int is_png = !png_sig_cmp(header, 0, 8);
	if (!is_png) 
	{
		fclose(file);
		throw runtime_error("Can't load png image file\n");
		return nullptr;
	}

	//create png struct
	png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
		NULL, NULL);
	if (!pngPtr) 
	{
		fclose(file);
		throw runtime_error("Can't load png image file\n");
		return nullptr;
	}

	//create png info struct
	png_infop infoPtr = png_create_info_struct(pngPtr);
	if (!infoPtr) 
	{
		png_destroy_read_struct(&pngPtr, (png_infopp)NULL, (png_infopp)NULL);
		fclose(file);
		throw runtime_error("Can't load png image file\n");
		return nullptr;
	}

	//create png info struct
	png_infop endInfo = png_create_info_struct(pngPtr);
	if (!endInfo) 
	{
		png_destroy_read_struct(&pngPtr, &infoPtr, (png_infopp)NULL);
		fclose(file);
		throw runtime_error("Can't load png image file\n");
		return nullptr;
	}

	//png error stuff, not sure libpng man suggests this.
	if (setjmp(png_jmpbuf(pngPtr))) 
	{
		png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);
		fclose(file);
		throw runtime_error("Can't load png image file\n");
		return nullptr;
	}

	//init png reading
	png_init_io(pngPtr, file);

	//let libpng know you already read the first 8 bytes
	png_set_sig_bytes(pngPtr, 8);

	// read all the info up to the image data
	png_read_info(pngPtr, infoPtr);

	//variables to pass to get info
	int bitDepth, colorType;
	png_uint_32 twidth, theight;

	// get info about png
	png_get_IHDR(pngPtr, infoPtr, &twidth, &theight, &bitDepth, &colorType,
		NULL, NULL, NULL);

	//update width and height based on png info
	size.x = twidth;
	size.y = theight;

	// Update the png info struct.
	png_read_update_info(pngPtr, infoPtr);

	// Row size in bytes.
	int rowbytes = png_get_rowbytes(pngPtr, infoPtr);

	// Allocate the image_data as a big block, to be given to opengl
	png_byte * data = new png_byte[rowbytes * theight];
	if (!data) 
	{
		//clean up memory and close stuff
		png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);
		fclose(file);
		throw runtime_error("Can't load png image file\n");
		return nullptr;
	}

	//row_pointers is for pointing to image_data for reading the png with libpng
	png_bytep * row_pointers = new png_bytep[theight];
	if (!row_pointers) 
	{
		//clean up memory and close stuff
		png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);
		delete[] data;
		fclose(file);
		throw runtime_error("Can't load png image file\n");
		return nullptr;
	}
	// set the individual row_pointers to point at the correct offsets of image_data
	for (uint i = 0; i < theight; ++i)
		row_pointers[theight - 1 - i] = data + i * rowbytes;

	//read the png into image_data through row_pointers
	png_read_image(pngPtr, row_pointers);

	//clean up memory and close stuff
	png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);
	delete[] row_pointers;
	fclose(file);

	auto ret       = new TextureData(size, data);
	ret->bitDepth  = bitDepth;
	ret->colorType = colorType;

	return ret;
}

void TextureData::save(const char * imagePath)
{
	/* create file */
	FILE *fp = fopen(imagePath, "wb");
	if (!fp)
		throw runtime_error("[save png] File %s could not be opened for writing");


	/* initialize stuff */
	auto png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png_ptr)
		throw runtime_error("[save png] png_create_write_struct failed");

	auto info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
		throw runtime_error("[save png] png_create_info_struct failed");

	if (setjmp(png_jmpbuf(png_ptr)))
		throw runtime_error("[save png] Error during init_io");

	png_init_io(png_ptr, fp);

	/* write header */
	if (setjmp(png_jmpbuf(png_ptr)))
		throw runtime_error("[save png] Error during writing header");

	png_set_IHDR(png_ptr, info_ptr, resolution.x, resolution.y,
		bitDepth, colorType, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);

	/* write bytes */
	if (setjmp(png_jmpbuf(png_ptr)))
		throw runtime_error("[save png] Error during writing bytes");

	const ubyte pixelSize = 4;
	// Allocate memory for one row (3 bytes per pixel - RGB)
	auto row = (png_bytep)malloc(pixelSize * resolution.x * sizeof(png_byte));

	// Write image data
	int x, y;
	for (y = resolution.y - 1; y >= 0; y--) 
	{
		for (x = 0; x < resolution.x; x++) 
		{
			row[x * pixelSize] = data[y * resolution.x * pixelSize 
				+ x * pixelSize];
			row[x * pixelSize + 1] = data[y * resolution.x * pixelSize 
				+ x * pixelSize + 1];
			row[x * pixelSize + 2] = data[y * resolution.x * pixelSize 
				+ x * pixelSize + 2];
			row[x * pixelSize + 3] = data[y * resolution.x * pixelSize 
				+ x * pixelSize + 3];
		}
		png_write_row(png_ptr, row);
	}

	// End write
	png_write_end(png_ptr, NULL);


	/* end write */
	if (setjmp(png_jmpbuf(png_ptr)))
		throw runtime_error("[save png] Error during end of write");

	png_write_end(png_ptr, NULL);

	/* cleanup heap allocation */
	if (fp != NULL) fclose(fp);
	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	if (row != NULL) free(row);

	fclose(fp);
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

void TextureData::modify(TextureData * data, const usvec2& offset, std::function<void(ubyte*, ubyte*)> blendFunction)
{
	//not fastest copy code
	uint16 i, j, row;
	for (i = 0; i < data->resolution.y; ++i)
	{
		row = i + offset.y;
		for (j = 0; j < data->resolution.x; ++j)
		{
			blendFunction(
				&(this->data[4 * (resolution.x * row + j + offset.x)]),
				&(data->data[4 * (data->resolution.x * i + j)]));
		}
	}
}

void TextureData::addGap(uint8 gap)
{
	usvec2 newResolution = resolution + usvec2(gap * 2, gap * 2);
	ubyte * newData = new ubyte[newResolution.x * newResolution.y * 4];

	for (uint i = 0; i < resolution.y; ++i)
	for (uint j = 0; j < resolution.x * 4; ++j)
		newData[(newResolution.x * 4) * (i + gap) + gap * 4 + j] = data[resolution.x * 4 * i + j];

	//fill gaps with color
	for (uint i = gap; i < newResolution.y - gap; ++i)
	for (uint j = 0; j < gap; ++j)
	{
		memcpy(
			&newData[newResolution.x * 4 * i + j * 4],
			&newData[newResolution.x * 4 * i + gap * 4],
			4);
		memcpy(
			&newData[newResolution.x * 4 * i + (resolution.x + gap) * 4 + j * 4],
			&newData[newResolution.x * 4 * i + (resolution.x + gap - 1) * 4],
			4);
	}

	for (uint i = 0; i < gap; ++i)
	for (uint j = 0; j < newResolution.x; ++j)
	{
		memcpy(
			&newData[newResolution.x * 4 * i + j * 4],
			&newData[newResolution.x * 4 * gap + j * 4],
			4);
		memcpy(
			&newData[newResolution.x * 4 * (resolution.y + gap + i) + j * 4],
			&newData[newResolution.x * 4 * (resolution.y + gap - 1) + j * 4],
			4);
	}

	delete[] data;
	data = newData;
	resolution = newResolution;
	this->gap = gap;
}

}