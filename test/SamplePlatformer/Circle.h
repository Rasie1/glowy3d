#pragma once
#include "Body.h"

namespace game
{

class Circle : public Body
{
public:
    Circle(glm::vec2 pos, float radius, glowy3d::vec2 bounce);
    virtual ~Circle() {}

    virtual void update(float dt);
    float getRadius() const;
    void  setRadius(float radius);

    virtual glm::vec2 getBounce() const;
    void setBounce(glm::vec2 bounce);

    virtual void collision(Body * other);
    virtual void collision(RigidLine * other);
    virtual void collision(Circle * other);

private:
    float radius;
    glm::vec2 bounce;
};

}
