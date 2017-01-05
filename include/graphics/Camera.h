#pragma once
#include "g2dMath.h"

namespace glowy3d
{

class Camera
{
public:
	Camera();

	//Returns Projection and View product matrix
	const mat3& getMatrix();

	void setPosition(const glm::vec3& position);
	void addPosition(const glm::vec3& offset);

	void addZoom(const float offset);
	void setDefaultZoom();

	void setUpDefaultMovementControls();
	void disableTransform();
	void enableTransform();

private:
	mat3 matrix;

	bool noTransform;
	mat3 noTransformMatrix;
};

}
