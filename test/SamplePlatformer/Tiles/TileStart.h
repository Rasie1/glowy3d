#pragma once
#include "Tile.h"

namespace game
{

class TileStart : public Tile
{
public:
    virtual bool isSolid() const;
    virtual std::string textureName() const;

    Actor * spawn(glm::vec2 pos);

private:
};

}