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
#include "Graphics/Camera.h"
#include "Base/Config.h"

namespace glowy2d
{
	Camera::Camera() :
		noTransform(false)
	{
		setDefaultZoom();
	}

	const mat2& Camera::getMatrix()
	{
		return matrix;
	}

	void Camera::setPosition(const vec2& position)
	{
		matrix[1][0] = position.x;
		matrix[1][1] = position.y;
	}

	void Camera::addPosition(const vec2& offset)
	{
		matrix[1][0] += offset.x;
		matrix[1][1] += offset.y;
	}

	void Camera::addZoom(const float offset)
	{
		matrix[0][0] += offset * matrix[0][0];
		matrix[0][1] += offset * matrix[0][1];
		matrix[1][0] += offset * matrix[1][0];
		matrix[1][1] += offset * matrix[1][1];
	}

	void Camera::setDefaultZoom()
	{
		float xxx = 2.f / 
			float(System::config->getScreenResolution().x);
		float yyy = 2.f / 
			float(System::config->getScreenResolution().y);

		matrix = mat2(xxx, yyy,
					  0.f, 0.f);
	}

	void Camera::setUpDefaultMovementControls()
	{
		static const float moveSpeed = 1.f;
		Input::setKeyCallback(Input::Keyboard::w, Input::PressType::hold,
			[&]()
		{
			addPosition(vec2(0.f, 
							 -moveSpeed * System::getDeltaTime()));
		});
		Input::setKeyCallback(Input::Keyboard::s, Input::PressType::hold,
			[&]()
		{
			addPosition(vec2(0.f, 
							 moveSpeed * System::getDeltaTime()));
		});
		Input::setKeyCallback(Input::Keyboard::d, Input::PressType::hold,
			[&]()
		{
			addPosition(vec2(-moveSpeed * System::getDeltaTime(), 
						     0.f));
		});
		Input::setKeyCallback(Input::Keyboard::a, Input::PressType::hold,
			[&]()
		{
			addPosition(vec2(moveSpeed * System::getDeltaTime(),
						     0.f));
		});
		Input::setKeyCallback(Input::Keyboard::space, Input::PressType::hold,
			[&]()
		{
			addZoom(-moveSpeed * System::getDeltaTime());
		});

		Input::setKeyCallback(Input::Keyboard::lshift, Input::PressType::hold,
			[&]()
		{
			addZoom(moveSpeed * System::getDeltaTime());
		});
	}

	void Camera::disableTransform()
	{
		if (!noTransform)
		{
			noTransform = true;
			noTransformMatrix = matrix;
			setDefaultZoom();
		}
	}

	void Camera::enableTransform()
	{
		if (noTransform)
		{
			noTransform = false;
			matrix = noTransformMatrix;
		}
	}
}