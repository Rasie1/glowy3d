#pragma once
#include <vector>
#include "Graphics/Layer.h"
#include "MapInfo.h"

namespace game
{

class CollisionData;
class Background;
class Actor;
class World
{
public:
    World(const MapInfo& map);
    ~World();

    int update(float dt);
private:
    void draw();
    glowy2d::Layer * mapLayer;
    Background * background;
    CollisionData * collisionData;
    std::vector<Actor*> actors;
};

}