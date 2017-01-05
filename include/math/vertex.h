#pragma once
#include "g2dMath.h"

namespace glowy3d
{

struct vertex
{
    vec3 position;
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

struct vertexn
{
    vec3 position;
    vec3 normal;
    vec2 texture;

    vertexn() {}
    vertexn(const vec3& position, 
            const vec3& normal, 
            const vec2& texture);
    vertexn(float x, float y, float z, 
            float nx, float ny, float nz,
            float u, float v);

    float x() const;
    float y() const;
    float z() const;
    float nx() const;
    float ny() const;
    float nz() const;
    float u() const;
    float v() const;
};

}
