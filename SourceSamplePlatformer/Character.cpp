#include "Character.h"
#include <algorithm>
#include "RigidLine.h"
#include "Walker.h"
#include "GlobalData.h"
#include "CollisionData.h"

using namespace glm;
namespace game
{

Character::Character(vec2 pos) :
    body(new Walker(pos)),
    jumpMomentum(-20.f),
    accelerationSpeed(8.f),
    airAccelerationSpeed(0.05f)
{

}

Character::~Character()
{
    delete body;
}

void Character::update(float dt)
{
    body->update(dt);
}

void Character::moveLeft()
{
    body->momentum(vec2(-getAcceleration(), 0));
}

void Character::moveRight()
{
    body->momentum(vec2(getAcceleration(), 0));
}

void Character::jump()
{
    if (!body->isGrounded())
        return;
    body->detachFromGround();
    body->momentum(vec2(0, jumpMomentum));
}

void Character::flyUp()
{
    body->momentum(vec2(0, -getAcceleration() - GlobalData::collisionData->getGravity().y));
}

void Character::flyDown()
{
    getBody()->momentum(vec2(0, getAcceleration()));
}

float Character::getAcceleration() const
{
    if (body->isGrounded())
        return accelerationSpeed;
    else
        return airAccelerationSpeed;
}

Body * Character::getBody()
{
    return body;
}

void Character::draw()
{
    body->draw();
}

vec2 Character::getPosition() const
{
    return body->getPosition();
}


vec2 Character::getPrevPosition() const
{
    return body->getPrevPosition();
}

}