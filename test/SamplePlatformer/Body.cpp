#include "Body.h"
#include <algorithm>
#include <iostream>
#include "Engine.h"
#include "GlobalData.h"
#include "CollisionData.h"

using namespace glm;
using namespace std;
namespace game
{

Body::Body(glm::vec2 pos) :
    pos(pos),
    layer(new glowy3d::Layer(4)),
    floating(false),
    solid(true),
    velocity(0.f, 0.f)
{
    layer->add("ukata.png");
    layer->setZOrder(-1.f);
    layer->setPosition(pos);
    prevPos = pos;
    layer->updateBuffer();
}

Body::~Body()
{

}

void Body::setPosition(vec2 pos)
{
    this->pos = pos;
}

void Body::addPosition(vec2 pos)
{
    this->pos += pos;
}

void Body::momentum(vec2 pos)
{
    velocity += pos;
}

void Body::update(float dt)
{
    if (dt > 0.3f)
        dt = 0.f;

    if (!isFloating())
        velocity += GlobalData::collisionData->getGravity() * dt;

    GlobalData::collisionData->collision(this);
    nextPosOffset = velocity * dt;

    prevPos = getPosition();
    addPosition(nextPosOffset);
    layer->setPosition(toRenderer(pos));
}

vec2 Body::getPosition() const
{
    return pos;
}

vec2 Body::getVelocity() const
{
    return velocity;
}

void Body::setVelocity(vec2 vel)
{
    velocity = vel;
}

void Body::addVelocity(vec2 vel)
{
    velocity += vel;
}

void Body::draw()
{
    layer->draw();
}

vec2 Body::getPrevPosition() const
{
    return prevPos;
}

bool Body::isFloating() const
{
    return floating;
}

void Body::setFloating(bool floating)
{
    this->floating = floating;
}

}
