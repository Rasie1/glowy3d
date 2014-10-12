#ifndef __AI_H__
#define __AI_H__

#include "cocos2d.h"
#include "Actor.h"
#include "Creature.h"
#include "Player.h"
#include "MapInfo.h"
#include "World.h"
#include "Libs.h"

USING_NS_CC;

class Actor;
class Creature;
class Player;

class AIStatePart : public Ref
{
public:
	static AIStatePart * create(Creature * creature);
	virtual bool init(Creature * creature);
	virtual void apply();
protected:
	Creature * creature;

	AIStatePart() {}
};

class AIStatePartAttackMove : public AIStatePart
{
	static AIStatePartAttackMove * create(Creature * creature);
	virtual bool init(Creature * creature);
	virtual void apply();
private:
	void searchForTarget();
	void attackTarget();

	Actor * target;
	AIStatePartAttackMove() {}
};

class AIState : public Ref
{
public:
	static AIState * create(Creature * creature);
	virtual bool init(Creature * creature);
	void apply();
protected:
	Creature * creature;
	std::vector<AIStatePart*> parts;
	AIState() {}
};

class AIStateFight : public AIState
{
public:
	static AIStateFight * create(Creature * creature);
	virtual bool init(Creature * creature);

protected:
	AIStateFight() {}
};

class AI : public Ref
{
public:
	static AI * create(Creature * creature);
	virtual bool init(Creature * creature);

	int getState();
	void setState(int number);
	void apply();
private:
	Creature * creature;
	int stateNumber;
	AIState * states[4];

	AI() {}
};

#endif