#include "TileGrass.h"

namespace game
{

bool TileGrass::isSolid() const
{
    return true;
}

std::string TileGrass::textureName() const
{
    return "TileGrass.png";
}

}