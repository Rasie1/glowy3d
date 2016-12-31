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
#include "Math/AdditionGLM.h"
#include "glm/detail/precision.hpp"
#include "glm/detail/type_int.hpp"

namespace glm
{

//Rectangle struct with float points
struct rect
{
	//Data

	//Represents upper left point of rectangle
	vec2 p1;
	//Represents lower right point of rectangle
	vec2 p2;


	//Rectangle struct with float points
	rect(const vec2& upperLeft, const vec2& lowerRight) : p1(upperLeft), p2(lowerRight) {}
	//Rectangle struct with float points. Construct with first point of 0
	rect(const vec2& lowerRight) : p1(vec2(0.f, 0.f)), p2(lowerRight) {}

	//Determines whether or not point inside the rectangle
	bool isInside(const vec2& point) const
	{
		return point.x >= p1.x && point.y >= p1.y &&
			point.x <= p2.x && point.y < p2.y;
	}

	//Calculates and returns dimensions of rectangle
	vec2 getSize() const
	{
		return p2 - p1;
	}

	//Returns true if given vector can fit inside this rectangle
	bool isFitting(vec2 rectSize) const
	{
		vec2 sz1 = getSize();
		return sz1.x >= rectSize.x && sz1.y >= rectSize.y;
	}

	//Returns true if given rectangle can fit inside this one
	bool isFitting(const rect& rectangle) const
	{
		return isFitting(rectangle.getSize());
	}

	rect getRotated() const
	{
		return rect(p1, vec2(p1.y, p1.x));
	}
};

//Rectangle struct with unsigned short points
struct usrect
{
	//Data

	//Represents upper left point of rectangle
	usvec2 p1;
	//Represents lower right point of rectangle
	usvec2 p2;

	//Rectangle struct with unsigned short points
	usrect(const usvec2& upperLeft, const usvec2& lowerRight) : p1(upperLeft), p2(lowerRight) {}
	//Rectangle struct with ushort points. Construct with first point of 0
	usrect(const usvec2& lowerRight) : p1(usvec2(0, 0)), p2(lowerRight) {}

	//Determines whether or not point inside the rectangle
	bool isInside(const usvec2& point) const
	{
		return point.x >= p1.x && point.y >= p1.y &&
			   point.x <= p2.x && point.y < p2.y;
	}

	//Calculates and returns dimensions of rectangle
	usvec2 getSize() const
	{
		return p2 - p1;
	}

	//Returns true if given vector can fit inside this rectangle
	bool isFitting(usvec2 rectSize) const
	{
		usvec2 sz1 = getSize();
		return sz1.x >= rectSize.x && sz1.y >= rectSize.y;
	}

	//Returns true if given rectangle can fit inside this one
	bool isFitting(const usrect& rectangle) const
	{
		return isFitting(rectangle.getSize());
	}

	usrect getRotated() const
	{
		return usrect(p1, usvec2(p1.y, p1.x));
	}
};
	
}

using glm::rect;
using glm::usrect;