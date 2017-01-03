#pragma once
#include "Body.h"
#include "math/AdditionGLM.h"

namespace game
{

class Circle;
class Walker;
class RigidLine : public Body
{
public:
    RigidLine(glowy3d::vec2 p1, glowy3d::vec2 p2);
    ~RigidLine() {}

    virtual void update(float dt);

    virtual void collision(Body * other);
    virtual void collision(Circle * other);
    virtual void collision(Walker * other);
    virtual void collision(glowy3d::vec2 lineP1, glowy3d::vec2 lineP2);

private:
    glowy3d::vec2 p1, p2;
    glowy3d::vec2 bounce;
    bool collided;
    bool horisontal;
};

}
