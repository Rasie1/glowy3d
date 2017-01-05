#include "math/vertex.h"
using namespace std;

namespace glowy3d
{

vertex::vertex(const vec3& position, const vec2& texture) :
	position(position),
	texture(texture)
{
}

vertex::vertex(float x, float y, float z, float u, float v) :
	position(x, y, z),
	texture(u, v)
{
}

float vertex::x() const
{
	return position.x;
}

float vertex::y() const
{
	return position.y;
}

float vertex::z() const
{
	return position.z;
}

float vertex::u() const
{
	return texture.x;
}

float vertex::v() const
{
	return texture.y;
}

}
