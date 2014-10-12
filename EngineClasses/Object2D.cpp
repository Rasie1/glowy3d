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
#include "Object2D.h"
namespace glowy2d
{
	Object2D::Object2D()
	{
		m_position = vec2(0.f, 0.f);
		m_scale = vec2(1.f, 1.f);
		m_rotation = vec2(0.f, 0.f);
	}

	Object2D::~Object2D()
	{

	}

	const vec2& Object2D::getPosition() const
	{
		return m_position;
	}

	void Object2D::setPosition(const vec2& position)
	{
		m_position = position;
	}

	void Object2D::addPosition(const vec2& offset)
	{
		m_position += offset;
	}

	const vec2& Object2D::getScale() const
	{
		return m_scale;
	}

	void Object2D::setScale(const vec2& scale)
	{
		m_scale = scale;
	}

	const vec2& Object2D::getRotation() const
	{
		return m_rotation;
	}

	void Object2D::setRotation(const vec2& rotation)
	{
		m_rotation = rotation;
	}

}