#pragma once
#include "g2dMath.h"

namespace glowy3d
{

struct vertex
{
	//Data
	vec2 position;
	float zOrder;
	vec2 texture;

	vertex() {}
	vertex(const vec3& position, const vec2& texture);
	vertex(float x, float y, float z, float u, float v);

	float x() const;
	float y() const;
	float z() const;
	float u() const;
	float v() const;
};

}
