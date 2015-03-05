#include "World.h"
#include <map>
#include <iostream>
#include "Math/AdditionGLM.h"
#include "Tiles/Tile.h"
#include "Background.h"
#include "CollisionData.h"
#include "GlobalData.h"
#include "Actor.h"
#include "Engine.h"
#include "Player.h"
#include "Graphics/Camera.h"

using namespace glm;
using namespace std;
using namespace glowy2d;
namespace game
{

void appendDirection(string& name, CollisionData * collisionData, usvec2 pos);
void randomizeIfPossible(string& name);

World::World(const MapInfo& map) :
    mapLayer(new glowy2d::Layer(2048, 2048)),
    background(new Background(map.backgroundImage)),
    collisionData(new CollisionData(map))
{
    std::map<string, Texture*> textures;
    for (uint i = 0; i < map.tiles.size();    ++i)
    for (uint j = 0; j < map.tiles[i].size(); ++j)
    {
        auto name = map.tiles[i][j]->textureName();
        if (name != "")
        {
            if (map.tiles[i][j]->isTextureSet())
                appendDirection(name, collisionData, usvec2(j + 1, i + 1));
            randomizeIfPossible(name);
            if (textures.find(name) == end(textures))
                textures[name] = mapLayer->addTexture(name.c_str());

            mapLayer->add(textures[name])
                    ->addPosition(toRenderer(vec2(j + 1, i)));
        }
    }
    mapLayer->setZOrder(0.8);
    mapLayer->updateBuffer();
    
    GlobalData::actors = &actors;
    GlobalData::collisionData = collisionData;

    for (uint i = 0; i < map.tiles.size();    ++i)
    for (uint j = 0; j < map.tiles[i].size(); ++j)
    {
        auto tile = map.tiles[i][j];
        auto actor = tile->spawn(usvec2(j + 1, i + 1));
        if (actor)
            actors.push_back(actor);
    }

    collisionData->traceContours(usvec2(0,0));
    System::camera->addPosition(vec2(0.f, 0.f));
}

World::~World()
{
    for (auto &actor : actors)
        delete actor;
    delete mapLayer;
    delete background;
    delete collisionData;
}

int World::update(float dt)
{
    for (auto &actor : actors)
        actor->update(dt);
    background->update(dt);
    /*System::camera->addPosition((vec2(-GlobalData::player->getPosition().x,
                                      GlobalData::player->getPosition().y)
                                    - GlobalData::player->getPrevPosition())
                                    / 32.f);*/
    draw();
    return 0;
}

void World::draw()
{
    background->draw();
    mapLayer->draw();
    for (auto &actor : actors)
        actor->draw();
}

void appendDirection(string& name, CollisionData * collisionData, usvec2 pos)
{
    auto t = usvec2(0, 1);
    auto tr = usvec2(1, 1);
    auto tl = usvec2(-1, 1);
    auto l = usvec2(-1, 0);
    auto r = usvec2(1, 0);
    auto b = usvec2(0,-1);
    auto bl = usvec2(-1, -1);
    auto br = usvec2(1, -1);
    auto insertPos = name.size() - 4;
    string postfix;
    
    if  (collisionData->check(pos + t) &&
        !collisionData->check(pos + tl) &&
        collisionData->check(pos + tr) &&
        collisionData->check(pos + bl) &&
        collisionData->check(pos + br) &&
        collisionData->check(pos + b) &&
        collisionData->check(pos + l) &&
        collisionData->check(pos + r))
        postfix = "_inside_tr";
    else
    if (collisionData->check(pos + t) &&
        collisionData->check(pos + tl) &&
        !collisionData->check(pos + tr) &&
        collisionData->check(pos + bl) &&
        collisionData->check(pos + br) &&
        collisionData->check(pos + b) &&
        collisionData->check(pos + l) &&
        collisionData->check(pos + r))
        postfix = "_inside_tl";
    else
    if (!collisionData->check(pos + t) &&
        !collisionData->check(pos + tr) &&
        collisionData->check(pos + bl) &&
        collisionData->check(pos + b) &&
        collisionData->check(pos + l) &&
        !collisionData->check(pos + r))
        postfix = "_corner_br";
    else
    if (!collisionData->check(pos + t) &&
        !collisionData->check(pos + tl) &&
        collisionData->check(pos + br) &&
        collisionData->check(pos + b) &&
        !collisionData->check(pos + l) &&
        collisionData->check(pos + r))
        postfix = "_corner_bl";
    else
    if (collisionData->check(pos + t) &&
        collisionData->check(pos + tl) &&
        collisionData->check(pos + tr) &&
        collisionData->check(pos + bl) &&
        !collisionData->check(pos + br) &&
        collisionData->check(pos + b) &&
        collisionData->check(pos + l) &&
        collisionData->check(pos + r))
        postfix = "_inside_bl";
    else
    if (collisionData->check(pos + t) &&
        collisionData->check(pos + tl) &&
        collisionData->check(pos + tr) &&
        !collisionData->check(pos + bl) &&
        collisionData->check(pos + br) &&
        collisionData->check(pos + b) &&
        collisionData->check(pos + l) &&
        collisionData->check(pos + r))
        postfix = "_inside_br"; 
    else
    if (collisionData->check(pos + t) &&
        collisionData->check(pos + tr) &&
        !collisionData->check(pos + bl) &&
        !collisionData->check(pos + b) &&
        !collisionData->check(pos + l) &&
        collisionData->check(pos + r))
        postfix = "_corner_tl";
    else
    if (collisionData->check(pos + t) &&
        collisionData->check(pos + tl) &&
        !collisionData->check(pos + br) &&
        !collisionData->check(pos + b) &&
        collisionData->check(pos + l) &&
        !collisionData->check(pos + r))
        postfix = "_corner_tr";
    else
    if (!collisionData->check(pos + t) &&
        collisionData->check(pos + b) &&
        collisionData->check(pos + l) &&
        collisionData->check(pos + r))
        postfix = "_bottom";
    else
    if (collisionData->check(pos + t) &&
        !collisionData->check(pos + b) &&
        collisionData->check(pos + l) &&
        collisionData->check(pos + r))
        postfix = "_top";
    else
    if (collisionData->check(pos + t) &&
        collisionData->check(pos + b) &&
        collisionData->check(pos + l) &&
        !collisionData->check(pos + r))
        postfix = "_right";
    else
    if (collisionData->check(pos + t) &&
        collisionData->check(pos + b) &&
        !collisionData->check(pos + l) &&
        collisionData->check(pos + r))
        postfix = "_left";

    name.insert(insertPos, postfix);
}

void randomizeIfPossible(string& name)
{

}


}