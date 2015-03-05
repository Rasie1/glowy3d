#pragma once
#include <string>
#include "Math/AdditionGLM.h"

namespace game
{

class Actor;
class Tile
{
public:
    virtual bool isSolid() const = 0;
    //return "" if it's untextured
    virtual std::string textureName() const = 0;
    virtual Actor * spawn(glm::vec2 pos);
    virtual bool isTextureSet() const;

private:
};

}