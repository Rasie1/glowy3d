#pragma once
#include <string>
#include "graphics/Layer.h"
#include "math/AdditionGLM.h"

namespace game
{
class Background
{
public:
    Background(const std::string& image);
    ~Background();

    int update(float dt);
    void draw();
private:
    glowy3d::Layer * backgroundLayer;
};

}
