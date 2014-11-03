#pragma once
#include "Base/IncludesEngine.h"

namespace glowy2d
{
	class Object3D
	{
	public:
		Object3D() {}
		~Object3D();
		float * vertex;
		float * color;

		int getVertexNum() const;

		const vec3& getPosition() const;
		virtual void setPosition(const vec3& position);

		const vec3& getDirection() const;
		virtual void setDirection(const vec3& direction);

		const vec3& getRotation() const;
		virtual void setRotation(const vec3& rotation);

	protected:
		vec3 m_position;
		vec3 m_direction;
		vec3 m_rotation;

		int m_vertexNum;
	};

}