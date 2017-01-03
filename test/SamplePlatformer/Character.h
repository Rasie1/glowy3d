#pragma once
#include "math/AdditionGLM.h"
#include "Actor.h"

namespace game
{

class Walker;
class Body;
class Character : public Actor
{
public:
    Character(glm::vec2 pos);
    ~Character();

    virtual void update(float dt);
    void draw();

    void moveLeft();
    void moveRight();
    void jump();
    void flyDown();
    void flyUp();
    glm::vec2 getPosition() const;
    glm::vec2 getPrevPosition() const;
    Body * getBody();

    float getAcceleration() const;

private:
    float accelerationSpeed;
    float airAccelerationSpeed;
    float jumpMomentum;

    bool isGrounded;

    Walker * body;
};

}
