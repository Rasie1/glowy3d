#include "Player.h"

Player * Player::create(const Vec2& pos, MapInfo * map)
{
	auto ref = new (std::nothrow) Player();
	if (ref && ref->init(pos, map))
	{
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

bool Player::init(const Vec2& pos, MapInfo * map)
{
	Creature::init(pos, map);
	//setColor(Color3B(100, 100, 255));
	speed = 3;
	health = 100;
	abilities.pushBack(AbilityAttack::create(map, this));
	abilities.pushBack(AbilityMoveTo::create(map, this));
	selectable = false;
	sleeping = false;
	teamNumber = TEAM_PLAYER;

	return true;
}