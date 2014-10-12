#ifndef __ABILITY_H__
#define __ABILITY_H__

#include "cocos2d.h"
#include "MapInfo.h"
#include "World.h"
#include "Libs.h"
#include "Actor.h"
#include "Creature.h"
#include "Player.h"
USING_NS_CC;

class World;
class Actor;
class Creature;
class Effect;
class Player;

class Ability : public Ref
{
public:
	static Ability * create(MapInfo * map, Actor * user, float delayBefore = 0.0f, int animationBefore = 0, float delayAfter = 0.0f, int animationAfter = 0);
	virtual void apply(Vec2 param = Vec2(0,0));
	virtual bool init(MapInfo * map, Actor * user, float delayAfter, float delayBefore);
	virtual void updateStats();
protected:
	Ability() {}
	MapInfo * map;
	Actor * user;
	float delayBefore, delayAfter; 
	bool usable;
	int animation; //Проблема: нужно чтобы она растягивалась по делею
	void setUsable(bool val);
	void applyDelayAfter();
};

class AbilityAttack : public Ability
{
public:
	static AbilityAttack * create(MapInfo * map, Actor * user);
	//pass attack direction as param
	virtual void apply(Vec2 param = Vec2(0, 0));
	virtual bool init(MapInfo * map, Actor * user);

private:
	AbilityAttack() {}
	int range, angle;
	Vector<Effect*> effects;
};

class AbilityMoveTo : public Ability
{
public:
	static AbilityMoveTo * create(MapInfo * map, Actor * user);
	//pass target location as param
	virtual void apply(Vec2 param = Vec2(0, 0));
	virtual bool init(MapInfo * map, Actor * user);
private:
	AbilityMoveTo() {}
	Vec2 moveLengthSquared;
};

#endif