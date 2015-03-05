#pragma once
#include <string>
#include "Graphics/Layer.h"
#include "Math/AdditionGLM.h"

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
    glowy2d::Layer * backgroundLayer;
};

}