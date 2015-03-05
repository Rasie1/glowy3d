#pragma once
#include "Math/AdditionGLM.h"
#include "Character.h"

namespace game
{

class Projectile;
class Player : public Character
{
public:
    Player(glm::vec2 pos);
    ~Player();

    virtual void update(float dt);

    void setAim(float radian);
    float getAim() const;
    Projectile * fire();

private:
    void initPlayerControls();

    float cooldown        = 2.f;
    float currentCooldown = 0.f;
    float aim = 0.f;
};

}