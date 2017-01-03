#include "Background.h"
#include <iostream>
#include "base/System.h"
#include "graphics/Camera.h"
#include "platforms/Window.h"

using namespace glm;
using namespace std;
using namespace glowy3d;
namespace game
{

Background::Background(const string& image) :
    backgroundLayer(new glowy3d::Layer(8, 2048))
{
    backgroundLayer->add((image + ".png").c_str());
    backgroundLayer->setZOrder(0.9f);
    backgroundLayer->updateBuffer();
    auto screen = -static_cast<vec2>(System::window->getSize());
    backgroundLayer->setPosition(screen / 2.f);
}

Background::~Background()
{
    delete backgroundLayer;
}

int Background::update(float dt)
{
    return 0;
}

void Background::draw()
{
    System::camera->disableTransform();
    backgroundLayer->draw();
    System::camera->enableTransform();
}

}
