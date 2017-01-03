#pragma once

namespace game
{

class Actor
{
public:
    virtual void update(float dt) = 0;
    virtual void draw() = 0; 

private:
};

}