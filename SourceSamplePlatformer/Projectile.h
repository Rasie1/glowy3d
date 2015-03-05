#pragma once
#include "Circle.h"
#include "Math/AdditionGLM.h"

namespace game
{

class Projectile : public Circle
{
public:
    Projectile(glm::vec2 position, glm::vec2 speed);
    ~Projectile() {}

    virtual void update(float dt);

};

}