#include "graphics/Camera.h"
#include "base/Config.h"

using namespace std;
using namespace glm;

using namespace std;
using namespace glm;

namespace glowy3d
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
