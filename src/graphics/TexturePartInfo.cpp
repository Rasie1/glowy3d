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
#include "Graphics/TexturePartInfo.h"

using namespace std;
using namespace glm;

namespace glowy3d
{
	TexturePartInfo::TexturePartInfo(const std::string& path, const rect& rectangle) : 
		path(path), 
		rectangle(rectangle)
	{
	}

	TexturePartInfo::~TexturePartInfo()
	{
	}

	const rect& TexturePartInfo::getRect() const
	{
		return rectangle;
	}

	void TexturePartInfo::setRect(const rect& newRect)
	{
		rectangle = newRect;
	}

	const std::string& TexturePartInfo::getPath() const
	{
		return path;
	}

	void TexturePartInfo::setPath(const std::string& newPath)
	{
		path = newPath;
	}
}
