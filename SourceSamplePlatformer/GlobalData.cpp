#include "GlobalData.h"

//using namespace glm;
using namespace std;

namespace game
{

std::vector<Actor*> * GlobalData::actors  = nullptr;
CollisionData * GlobalData::collisionData = nullptr;
Player * GlobalData::player = nullptr;
const float GlobalData::tilesize = 128;

}