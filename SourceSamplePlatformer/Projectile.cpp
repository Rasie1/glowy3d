#include "Projectile.h"

using namespace glm;
namespace game
{

Projectile::Projectile(vec2 position, vec2 speed) :
    Circle(position, 0.5f, vec2(1.f, 1.0f))
{

}

void Projectile::update(float dt)
{
    Circle::update(dt);
}

}