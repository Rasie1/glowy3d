#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "cocos2d.h"
#include "Actor.h"
#include "MapInfo.h"
#include "World.h"
USING_NS_CC;

class World;
class Actor;

class Effect : public Ref
{
public:
	static Effect * create(Actor * actor);
	//returns 1 if done
	virtual bool apply();
	virtual bool init(Actor * actor);
protected:
	Actor * target;
	Effect() {}
};

class EffectInstantDamage : public Effect
{
public:
	static EffectInstantDamage * create(Actor * actor, int damage);
	virtual bool apply();
	virtual bool init(Actor * actor, int damage);
protected:
	int dmg;
	EffectInstantDamage() {}
};

class EffectMoveTo : public Effect
{
public:
	static EffectMoveTo * create(Actor * actor, float speed, Vec2 pos);
	virtual bool apply();
	virtual bool init(Actor * actor, float speed, Vec2 pos);
private:
	Vec2 pos;
	Vec2 delta;
	float speed;
	float distanceSquared;
	EffectMoveTo() {}
	bool isDone();
};

#endif