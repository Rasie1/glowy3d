#pragma once
#include "Tile.h"

namespace game
{

class TileEmpty : public Tile
{
public:
    virtual bool isSolid() const;
    virtual std::string textureName() const;

private:
};

}