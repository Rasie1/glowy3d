#pragma once
#include <vector>
#include "graphics/Layer.h"
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
    glowy3d::Layer * mapLayer;
    Background * background;
    CollisionData * collisionData;
    std::vector<Actor*> actors;
};

}
