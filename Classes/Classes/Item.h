#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "Actor.h"
#include "MapInfo.h"
#include "MapGenerator.h"
#include "Ability.h"
#include "Effect.h"
#include "World.h"
#include "Libs.h"
#include "AAnimation.h"
#include "InterfaceBase.h"
USING_NS_CC;

class World;
class Actor;
class Creature;
class Effect;
class AAnimation;
class MapInfo;

class Item : public Ref
{
public:
	static Item * create();
	bool init();
private:
	Item() {}
};


#endif