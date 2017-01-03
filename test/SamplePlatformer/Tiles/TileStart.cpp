#include "TileStart.h"
#include <iostream>
#include "../Player.h"
#include "math/AdditionGLM.h"

namespace game
{

bool TileStart::isSolid() const
{
    return false;
}

std::string TileStart::textureName() const
{
    return "";
}

Actor * TileStart::spawn(glm::vec2 pos)
{
    return new Player(pos);
}

}
