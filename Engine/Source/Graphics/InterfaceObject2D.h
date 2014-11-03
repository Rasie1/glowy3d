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
#include "glm/glm.hpp"
using glm::vec2;

namespace glowy2d
{
	//Virtual class for objects capable of changing position,
	//rotation, scaling, anchorPoints and zOrder
	class InterfaceObject2D
	{
	public:
		virtual vec2 getPosition() const = 0;
		virtual void setPosition(const vec2& pos) = 0;
		virtual void addPosition(const vec2& offset) = 0;

		virtual float getRotation() const = 0;
		virtual void setRotation(const float pos) = 0;
		virtual void addRotation(const float offset) = 0;

		virtual vec2 getScale() const = 0;
		virtual void setScale(const vec2& scale) = 0;
		virtual void addScale(const vec2& offset) = 0;

		virtual float getScaleX() const = 0;
		virtual void setScaleX(const float scale) = 0;
		virtual void addScaleX(const float offset) = 0;

		virtual float getScaleY() const = 0;
		virtual void setScaleY(const float scale) = 0;
		virtual void addScaleY(const float offset) = 0;

		virtual float getZOrder() const = 0;
		virtual void setZOrder(const float zorder) = 0;
		virtual void addZOrder(const float offset) = 0;

		vec2 getOrigin() const;
		void setOrigin(const vec2& pos);
		void addOrigin(const vec2& offset);

	private:
		vec2 origin;
	};

}