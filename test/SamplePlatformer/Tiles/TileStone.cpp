#include "TileStone.h"

namespace game
{

bool TileStone::isSolid() const
{
    return true;
}

bool TileStone::isTextureSet() const
{
    return true;
}

std::string TileStone::textureName() const
{
    return "Tiles/stone.png";
}

}