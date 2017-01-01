#pragma once
#include "g2dMath.h"

namespace glowy3d
{

class Camera
{
public:
	Camera();

	//Returns Projection and View product matrix
	const mat2& getMatrix();

	void setPosition(const vec2& position);
	void addPosition(const vec2& offset);

	void addZoom(const float offset);
	void setDefaultZoom();

	void setUpDefaultMovementControls();
	void disableTransform();
	void enableTransform();

private:
	mat2 matrix;

	bool noTransform;
	mat2 noTransformMatrix;
};

}
