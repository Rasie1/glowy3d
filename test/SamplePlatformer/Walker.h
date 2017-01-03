#pragma once
#include "Circle.h"

namespace game
{

class Walker : public Circle
{
public:
    Walker(glm::vec2 pos);

    virtual void update(float dt);

    void checkGrounded();
    void attachToGround(float platformLeft, 
                        float platformRight);
    void detachFromGround();
    bool isGrounded() const;

    virtual void collision(Body * other);
    virtual void collision(RigidLine * other);

    glm::vec2 getBounce() const override;

private:
    bool  grounded;
    float groundedHeight;
    float groundedLeft;
    float groundedRight;
};

}