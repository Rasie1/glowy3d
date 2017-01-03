#pragma once
#include "Projectile.h"

namespace game
{

class Rocket : public Projectile
{
public:
    Rocket(glm::vec2 position, float aim);
    ~Rocket() {}

    virtual void update(float dt);

private:
    float trailFrequency = 0.3f;
    float lastTrail = 0;
};

}