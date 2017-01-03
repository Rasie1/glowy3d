#pragma once
#include "graphics/Layer.h"
#include "math/AdditionGLM.h"
#include "Actor.h"

namespace game
{

class CollisionData;
class RigidLine;
class Character;
class Body : public Actor
{
public:
    Body(glm::vec2 pos);
    virtual ~Body();

    virtual void update(float dt);
    void draw();

    glm::vec2 getPosition() const;
    glm::vec2 getPrevPosition() const;
    void      setPosition(glm::vec2 pos);
    void      addPosition(glm::vec2 pos);
    void      momentum(glm::vec2 pos);

    glm::vec2 getVelocity() const;
    void      setVelocity(glm::vec2 vel);
    void      addVelocity(glm::vec2 vel);
    bool isFloating() const;
    void setFloating(bool floating);

    virtual void collision(Body * other) {}
    virtual void collision(RigidLine * other) {}
    virtual void collision(Character * other) {}

private:
    glm::vec2 pos;
    glm::vec2 prevPos;
    glm::vec2 nextPosOffset;

    glm::vec2 velocity;

    glowy3d::Layer * layer;

    bool floating;
    bool solid;
};

}
