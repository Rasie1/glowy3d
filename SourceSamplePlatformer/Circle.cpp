#include "Circle.h"
#include "RigidLine.h"
#include "Body.h"

using namespace glm;
namespace game
{

Circle::Circle(vec2 pos, float radius, vec2 bounce) :
    Body(pos),
    bounce(bounce),
    radius(radius)
{
}

void Circle::update(float dt)
{
    Body::update(dt);
}

float Circle::getRadius() const
{
    return radius;
}

void Circle::setRadius(float radius)
{
    this->radius = radius;
}

void Circle::collision(Body * other)
{
    other->collision(this);
}

void Circle::collision(RigidLine * other)
{
    other->collision(this);
}

void Circle::collision(Circle * other)
{

}

void Circle::setBounce(vec2 bounce)
{
    this->bounce = bounce;
}

vec2 Circle::getBounce() const
{
    return bounce;
}

}