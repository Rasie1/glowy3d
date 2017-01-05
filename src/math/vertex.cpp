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

vertexn::vertexn(const vec3& position, 
                 const vec3& normal,
                 const vec2& texture) :
    position(position),
    normal(normal),
    texture(texture)
{
}

vertexn::vertexn(float x, float y, float z, 
                 float nx, float ny, float nz,
                 float u, float v) :
    position(x, y, z),
    normal(nx, ny, nz),
    texture(u, v)
{
}

float vertexn::x() const
{
    return position.x;
}

float vertexn::y() const
{
    return position.y;
}

float vertexn::z() const
{
    return position.z;
}

float vertexn::nx() const
{
    return position.x;
}

float vertexn::ny() const
{
    return position.y;
}

float vertexn::nz() const
{
    return position.z;
}

float vertexn::u() const
{
    return texture.x;
}

float vertexn::v() const
{
    return texture.y;
}

}
