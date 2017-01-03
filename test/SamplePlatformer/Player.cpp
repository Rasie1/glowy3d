#include "Player.h"
#include <algorithm>
#include <iostream>
#include "Engine.h"
#include "platforms/Input.h"
#include "platforms/Window.h"
#include "graphics/Camera.h"
#include "Body.h"
#include "GlobalData.h"

using namespace glm;
using namespace std;
using namespace glowy3d;
namespace game
{


Player::Player(vec2 pos) :
    Character(pos)
{
    initPlayerControls();
    GlobalData::player = this;
    System::camera->addZoom(-0.75);
}

Player::~Player()
{

}

void Player::update(float dt)
{
    Character::update(dt);
    System::camera->setPosition(vec2(getPosition().x / -GlobalData::tilesize,
                                     getPosition().y / GlobalData::tilesize) * 10.f);
}

void Player::initPlayerControls()
{

    Input::setKeyCallback(Input::Keyboard::up, Input::PressType::press,
        [&]()
    {
        jump();
    });
    Input::setKeyCallback(Input::Keyboard::rshift, Input::PressType::hold,
        [&]()
    {
        flyUp();
    });
    Input::setKeyCallback(Input::Keyboard::down, Input::PressType::hold,
        [&]()
    {
        flyDown();
    });
    Input::setKeyCallback(Input::Keyboard::right, Input::PressType::hold,
        [&]()
    {
        moveRight();
    });
    Input::setKeyCallback(Input::Keyboard::left, Input::PressType::hold,
        [&]()
    {
        moveLeft();
    });
}

void Player::setAim(float radian)
{
    this->aim = aim;
    //there is missing stuff
}

float Player::getAim() const
{
    return aim;
}
 
Projectile * Player::fire()
{
    return nullptr;
    //return new Rocket(getPosition(), aim);
}

}
