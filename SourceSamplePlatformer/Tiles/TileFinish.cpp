#include "TileFinish.h"
#include "Math/AdditionGLM.h"
//#include "Finish.h"

namespace game
{

bool TileFinish::isSolid() const
{
    return false;
}

std::string TileFinish::textureName() const
{
    return "TileFinish.png";
}

Actor * TileFinish::spawn(glm::usvec2 pos)
{
    return nullptr;
    //return new Finish(pos);
}

}