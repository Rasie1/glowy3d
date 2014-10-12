#include "stdafx.h"
#include "Object3D.h"

namespace glowy2d
{

	int Object3D::getVertexNum() const
	{
		return m_vertexNum;
	}

	Object3D::~Object3D()
	{
		delete[] vertex;
		delete[] color;
	}


	const vec3& Object3D::getPosition() const
	{
		return m_position;
	}

	void Object3D::setPosition(const vec3& position)
	{
		m_position = position;
	}

	const vec3& Object3D::getDirection() const
	{
		return m_direction;
	}

	void Object3D::setDirection(const vec3& direction)
	{
		m_direction = direction;
	}

	const vec3& Object3D::getRotation() const
	{
		return m_rotation;
	}

	void Object3D::setRotation(const vec3& rotation)
	{
		m_rotation = rotation;
	}

}