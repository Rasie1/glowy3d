#pragma once
#include <vector>
#include "Math/AdditionGLM.h"

namespace game
{

class Actor;
class CollisionData;
class Player;
class GlobalData
{
public:
    static std::vector<Actor*> * actors;
    static CollisionData * collisionData;
    static Player * player;
    static const float tilesize;
};


inline glm::vec2 toWorld(glm::vec2 point)
{
    return glm::vec2(point.x / GlobalData::tilesize, -point.y / GlobalData::tilesize);
}

inline glm::vec2 toRenderer(glm::vec2 point)
{
    return glm::vec2(point.x * GlobalData::tilesize, -point.y * GlobalData::tilesize);
}

}