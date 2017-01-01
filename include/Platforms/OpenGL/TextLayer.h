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
#ifdef R_OGL
#include "g2dMath.h"

namespace glowy3d
{

class TextLayer
{
public:
	TextLayer(const std::string& label = "", vec2 position = vec2(0.f, 0.f), float size = 8.f);
	~TextLayer() {}

	void setText(const std::string& text);
	void addText(const std::string& text);
	string getText() const;

	void setPosition(vec2 pos);
	void addPosition(vec2 pos);
	vec2 getPosition() const;

	//width
	//line break
	//letter spacing
	//letter height scale


private:
	vec2 position;
	std::string label;
	uint size;
};

}
#endif
