#include "Walker.h"
#include "RigidLine.h"
#include <iostream>

using namespace glm;
namespace game
{

Walker::Walker(glm::vec2 pos) :
    Circle(pos, 1.f, vec2(1.0f, 1.f)),
    grounded(false)
{

}

void Walker::update(float dt)
{
    Circle::update(dt);
    if (grounded)
    {
        setVelocity(getVelocity() * 0.999f * dt);
        checkGrounded();
        if (getPosition().y > groundedHeight)
            setPosition(vec2(getPosition().x,
                             getPrevPosition().y));
    }
}

void Walker::checkGrounded()
{
    if (getPosition().y < groundedHeight - 0.01f ||
        getPosition().x < groundedLeft           ||
        getPosition().x > groundedRight)
    {
        detachFromGround();
    }
}

void Walker::attachToGround(float platformLeft, float platformRight)
{
    setFloating(true);
    groundedHeight = getPosition().y;
    groundedLeft = platformLeft - getRadius();
    groundedRight = platformRight + getRadius();
    grounded = true;
}

void Walker::detachFromGround()
{
    grounded = false;
    setFloating(false);
}

bool Walker::isGrounded() const
{
    return grounded;
}

void Walker::collision(Body * other)
{
    other->collision(this);
}

void Walker::collision(RigidLine * other)
{
    other->collision(this);
}

vec2 Walker::getBounce() const
{
    if (grounded)
        return vec2(0.51f, 0.51f);
    else
        return Circle::getBounce();
}

}