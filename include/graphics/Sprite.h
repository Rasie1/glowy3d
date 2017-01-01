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
#include "g2dMath.h"
#include "Math/quad.h"

namespace glowy3d
{

class Texture;
class Sprite
{
public:
	Sprite(quad * vboPointer);
	~Sprite();

	bool isHidden() const;
	void setHidden(bool isHidden);

	vec2 getPosition() const;
	void setPosition(const vec2& pos);
	void addPosition(const vec2& offset);

	vec2 getScale() const;
	void setScale(const vec2& scale);
	void addScale(const vec2& offset);

	vec2 getOrigin() const;
	void setOrigin(const vec2& pos);
	void addOrigin(const vec2& offset);

	float getScaleX() const;
	void setScaleX(const float scale);
	void addScaleX(const float offset);

	float getScaleY() const;
	void setScaleY(const float scale);
	void addScaleY(const float offset);

	float getRotation() const;
	void setRotation(const float rotation);
	void addRotation(const float offset);

	float getZOrder() const;
	void setZOrder(const float zorder);
	void addZOrder(const float offset);

	Texture * getTexture() const;
	void setTexture(Texture * texture);

private:
	vec2 position, 
		 scale,
		 origin;
	float rotation;
	bool is_hidden = false;

	quad * coords;
	Texture * texture;

	bool has_changed = true;

	void pointToVbo(float * vbo);
};

}
