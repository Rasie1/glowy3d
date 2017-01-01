/****************************************************************************
This file is part of glowy3d.

Copyright (c) 2015 Kvachev 'Rasie1' V. D.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "epc.h"
#include "Graphics/LineLayer.h"
#include "Graphics/Texture.h"
#include "Graphics/Sprite.h"

using namespace std;

using namespace std;
using namespace glm;

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
