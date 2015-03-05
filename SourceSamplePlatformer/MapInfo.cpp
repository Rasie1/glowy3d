#include "MapInfo.h"
#include <fstream>
#include <algorithm>
#include <string>
#include <iterator>
#include <iostream>
#include "Tiles/TileGrass.h"
#include "Tiles/TileStone.h"
#include "Tiles/TileEmpty.h"
#include "Tiles/TileStart.h"
#include "CollisionData.h"

using namespace std;
using namespace glm;
namespace game
{

MapInfo::MapInfo(const string& name) :
    tiles(loadMap(name))
{
}

MapInfo::~MapInfo()
{
    for (auto &row : tiles)
    for (auto &tile : row)
        delete tile;
}

std::vector<std::vector<Tile*>> MapInfo::loadMap(const string& name)
{
    ifstream f;
    f.open("Maps/" + name + ".txt");
    if (!f.good())
        throw ifstream::failure("Failed to open map \"" + name +"\"!");

    usvec2 size;
    f >> size.x >> size.y;

    vector<vector<Tile*>> tiles(size.y);
    for (unsigned i = 0; i < size.y; ++i)
    for (unsigned j = 0; j < size.x; ++j)
    {
        char c;
        f >> c;
        switch (c)
        {
            case 'e':
            {
                tiles[i].push_back(new TileEmpty());
                break;
            }
            case 'g':
            {
                tiles[i].push_back(new TileGrass());
                break;
            }
            case 'r':
            {
                tiles[i].push_back(new TileStone());
                break;
            }
            case 'R':
            {
                tiles[i].push_back(new TileStone());
                CollisionData::addTracingPoint(usvec2(j, i));
                break;
            }
            case 's':
            {
                tiles[i].push_back(new TileStart());
                break;
            }
            default:
                --j;
        }
    }

    return tiles;
}

bool MapInfo::collision(glm::usvec2 pos) const
{
    return tiles[pos.y][pos.x]->isSolid();
}

}