#pragma once
#include "math/AdditionGLM.h"
#include "Body.h"

namespace game
{

class Finish : public Body
{
public:
    Finish(glm::usvec2 pos);
    ~Finish();

    void update(float dt);

private:
};

}
