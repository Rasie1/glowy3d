#pragma once
#include "Body.h"
#include "Math/AdditionGLM.h"

namespace game
{

class Circle;
class Walker;
class RigidLine : public Body
{
public:
    RigidLine(glm::vec2 p1, glm::vec2 p2);
    ~RigidLine() {}

    virtual void update(float dt);

    virtual void collision(Body * other);
    virtual void collision(Circle * other);
    virtual void collision(Walker * other);
    virtual void collision(glm::vec2 lineP1, glm::vec2 lineP2);

private:
    vec2 p1, p2;
    vec2 bounce;
    bool collided;
    bool horisontal;
};

}