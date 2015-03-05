#include "TileEmpty.h"

namespace game
{

bool TileEmpty::isSolid() const
{
    return false;
}

std::string TileEmpty::textureName() const
{
    return "";
}

}