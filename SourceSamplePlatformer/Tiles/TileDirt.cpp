#include "TileDirt.h"

namespace game
{

bool TileDirt::isSolid() const
{
    return true;
}

std::string TileDirt::textureName() const
{
    return "TileDirt.png";
}

}