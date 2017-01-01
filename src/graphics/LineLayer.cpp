#include "graphics/LineLayer.h"
#include "graphics/Texture.h"
#include "graphics/Sprite.h"

using namespace std;

namespace glowy3d
{

LineLayer::LineLayer(uint maxSprites, string image) :
    Layer(maxSprites)
{
    lineTexture = addTexture(image.c_str());
    updateBuffer();
}

LineLayer::~LineLayer()
{
    delete lineTexture;
}

void LineLayer::addLine(vec2 p1, vec2 p2, float frequency, float zOrder)
{
    dvec2 step = dvec2(p2.x - p1.x, p2.y - p1.y) / static_cast<double>(frequency);
    for (dvec2 i = p1; glm::distance(i, static_cast<dvec2>(p2)) > 10.0; i += step)
        add(lineTexture)->addPosition(i);
    setZOrder(zOrder);
    updateBuffer();
}


}
