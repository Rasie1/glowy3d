#include "RigidLine.h"
#include "Circle.h"
#include <iostream>
#include "Walker.h"

using namespace glm;
namespace game
{

RigidLine::RigidLine(vec2 p1, vec2 p2) :
    Body(p1),
    p1(p1),
    p2(p2),
    horisontal(abs(p1.x - p2.x) > abs(p1.y - p2.y)),
    collided(false)
{
    if (this->p1.x > this->p2.x)
        std::swap(this->p1, this->p2);

    bounce = vec2(1.f, 1.f);
}


void RigidLine::update(float dt)
{
    Body::update(dt);
}

void RigidLine::collision(Body * other)
{
    other->collision(this);
}

void RigidLine::collision(Walker * other)
{
    collided = false;
    collision(dynamic_cast<Circle*>(other));
    

    if (!other->isGrounded() && 
        horisontal && 
        collided && 
        p1.y > other->getPosition().y)
            other->attachToGround(p1.x, p2.x);

    if (collided)
        other->setPosition(other->getPrevPosition());
}

bool intersects(vec2 p1, vec2 p2, vec2 c, float r, vec2& pointOnLineClosestToCircle)
{
    auto lineUnitVector = normalize(p2 - p1);
    auto lineEndToCircle = c - p1;
    auto projection = dot(lineEndToCircle, lineUnitVector);

    if (projection <= 0)
        pointOnLineClosestToCircle = p1;
    else if (projection >= length(p2 - p1))
        pointOnLineClosestToCircle = p2;
    else
        pointOnLineClosestToCircle =
            vec2(p1.x + lineUnitVector.x * projection,
                 p1.y + lineUnitVector.y * projection);

    auto circleToLineDistance = distance(pointOnLineClosestToCircle, c);

    return circleToLineDistance < r;
}

void RigidLine::collision(Circle * other)
{
    vec2 pointOnLineClosestToCircle;

    //collision(other->getPosition(), other->getPosition() + other->getVelocity());
    if (intersects(
            p1, 
            p2, 
            other->getPosition(), 
            other->getRadius(), 
            pointOnLineClosestToCircle))
    {
        auto circleToClosestPointOnLine = other->getPosition() - pointOnLineClosestToCircle;

        auto bounceNormal = normalize(circleToClosestPointOnLine);

        auto k = dot(other->getVelocity(), bounceNormal);
        other->addVelocity(
            vec2(bounceNormal.x * (-2.f) * k * (other->getBounce().x) * (bounce.x),
                 bounceNormal.y * (-2.f) * k * (other->getBounce().y) * (bounce.y)));
        collided = true;
    }
}

void RigidLine::collision(glm::vec2 lineP1, glm::vec2 lineP2)
{
    auto p0_x = lineP1.x;
    auto p0_y = lineP1.y;
    auto p1_x = lineP2.x;
    auto p1_y = lineP2.y;
    auto p2_x = p1.x;
    auto p2_y = p1.y;
    auto p3_x = p2.x;
    auto p3_y = p2.y;

    auto s1_x = p1_x - p0_x;
    auto s1_y = p1_y - p0_y;
    auto s2_x = p3_x - p2_x;
    auto s2_y = p3_y - p2_y;
     
    auto s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / 
             (-s2_x * s1_y + s1_x * s2_y);
    auto t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / 
             (-s2_x * s1_y + s1_x * s2_y);
     
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
        collided = true;
}

}