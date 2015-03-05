#pragma once
#include "Tile.h"

namespace game
{

class TileFinish : public Tile
{
public:
    virtual bool isSolid() const;
    virtual std::string textureName() const;

    Actor * spawn(glm::usvec2 pos);
    
private:
};

}