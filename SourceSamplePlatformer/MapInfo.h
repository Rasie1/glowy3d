#pragma once
#include <vector>
#include <string>
#include "Math/AdditionGLM.h"

namespace game
{

class Tile;
class MapInfo
{
public:
    MapInfo(const std::string& name);
    ~MapInfo();

    bool collision(glm::usvec2 pos) const;
    
    std::vector<std::vector<Tile*>> tiles;
    std::string backgroundImage = "sky";

private:

    std::vector<std::vector<Tile*>> loadMap(const std::string& name);
};

}