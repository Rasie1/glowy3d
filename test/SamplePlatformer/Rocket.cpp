#include "Rocket.h"

using namespace glm;
namespace game
{

Rocket::Rocket(vec2 position, float speed) :
    Projectile(position, vec2(speed, speed))
{

}

void Rocket::update(float dt)
{
    Projectile::update(dt);
}

}