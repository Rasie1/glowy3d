#pragma once
#include "graphics/Layer.h"
#include <string>

namespace glowy3d
{

class LineLayer : public Layer
{
public:
    LineLayer(uint maxSprites = 1024, std::string image = "blue.png");
    ~LineLayer();
    void addLine(vec2 p1, vec2 p2, float frequency, float zOrder);
private:
    Texture* lineTexture;
};

}
