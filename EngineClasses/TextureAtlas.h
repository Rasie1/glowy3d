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
#include "TextureInfo.h"
#include "TextureData.h"
#include "Tex2D.h"


namespace glowy2d
{
	struct AtlasNode
	{
		AtlasNode(usrect rectangle) : r(rectangle) {}
		AtlasNode * child[2];
		usrect r;
		TextureData * data;
		bool closed = false;
		bool leaf = true;
		bool cutx = false;
		AtlasNode * insert(TextureData * tex);
	};

	class TextureAtlas
	{
	public:
		//A texture atlas. Use add() to add textures
		//to atlas and then generate() to assemble them and
		//prepare for drawing. add() returns a TextureInfo 
		//object that is passed to sprites.
		TextureAtlas(unsigned short maxSize);
		~TextureAtlas();

		//When you finished to add your images to the atlas,
		//call generate() to get them ready for drawing
		TextureInfo * add(TextureData * data);

		void bind();

	private:
		AtlasNode * tree;
		TextureData * data;
		Tex2D tex;
		

	};

}