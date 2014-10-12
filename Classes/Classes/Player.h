#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "MapInfo.h"
#include "Ability.h"
#include "Effect.h"
#include "Libs.h"
#include "AAnimation.h"
#include "InterfaceBase.h"
#include "Item.h"
#include "MapPath.h"
#include "Actor.h"
#include "Creature.h"

USING_NS_CC;

class World;
class Ability;
class Effect;
class AAnimation;
class InterfacePart;
class MapPath;
class MapInfo;
class Item;
class ItemActor;
class AnimationSet;
class Actor;
class Creature;
/* MOVED TO ACTOR.H DUE TO SHITTY #INCLUDE SYSTEM

class Player : public Creature
{
public:
	static Player * create(const Vec2& pos, MapInfo * map);
	virtual bool init(const Vec2& pos, MapInfo * map);

protected:
	Player() {}
};*/
#endif