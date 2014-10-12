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
#include "Camera.h"

namespace glowy2d
{
	Camera::Camera()
	{
		setDefaultZoom();
	}

	const mat4& Camera::getMatrix()
	{
		return projectionMatrix;
	}

	void Camera::setPosition(const vec2& position)
	{
		projectionMatrix[3][0] = position.x;
		projectionMatrix[3][1] = position.y;
	}

	void Camera::addPosition(const vec2& offset)
	{
		projectionMatrix[3][0] += offset.x;
		projectionMatrix[3][1] += offset.y;
	}

	void Camera::addZoom(const float offset)
	{
		projectionMatrix[0][0] += offset * projectionMatrix[0][0];
		projectionMatrix[1][1] += offset * projectionMatrix[1][1];
		projectionMatrix[3][0] += offset * projectionMatrix[3][0];
		projectionMatrix[3][1] += offset * projectionMatrix[3][1];
	}

	void Camera::setDefaultZoom()
	{
		projectionMatrix = mat4(2.f / float(SCREEN_WEED), 0.f, 0.f, 0.f,
								0.f, 2.f / float(SCREEN_HATE), 0.f, 0.f,
								0.f, 0.f, 1.f, 0.f,
								0.f, 0.f, 0.f, 1.f);
	}

}