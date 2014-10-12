#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "cocos2d.h"
#include "MapInfo.h"
#include "Actor.h"
#include "Ability.h"
#include "Effect.h"
#include "Libs.h"
#include "AAnimation.h"
#include "InterfaceBase.h"
#include "Item.h"
#include "MapPath.h"
#include "CreatureStats.h"

USING_NS_CC;

class Actor;
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
/* MOVED TO ACTOR.H DUE TO SHITTY #INCLUDE SYSTEM

//Actor, who can move and wear items
class Creature : public Actor
{
public:
	static Creature * create(const Vec2& pos, MapInfo * map);
	virtual bool init(const Vec2& pos, MapInfo * map);

	//Called every frame
	virtual void act(float timeCoefficient);
	//Called ten times a second
	virtual void actTenth();

	void attack(Actor * target);
	void moveTo(const Vec2& target);
	void moveBy(const Vec2& delta);
	void takeDamage(Actor * user, int damage, int type = 0);
	
	float getSpeed();
	float getAttackRange();
	float getAttackRangeSq();

	virtual void die();

protected:
	Creature() {}
	//State section
	bool isMoving, isAttacking, isCasting;

	//Movement section
	MapPath * movingQueue;
	//Moves creature if needed
	void moveStep(float timeCoefficient);
	//Returns true if collided with something
	bool checkMoveCollision();
	//Stops moving if something is in the way
	void updatePathIfCollided();
	//Calculate how to move on a straight line to the point
	void setupMovement(const Vec2& point);
	//Process the next point in movingQueue
	void moveProcessNextPoint();
	void stopMoving();
	float moveLength;
	Vec2 moveVector;
	//It's squared because of movement optimisation
	float speed;
	float currentSpeed;
	Vec2 movementTarget;
	void updateCollisionMap();
	Vec2 prevTilePos;

	//Attack section

	//This should be squared too
	int attackRange;
	bool attackOnMoveDone;

	//Direction Section
	size_t direction;
	float directionAngleRadians;
	size_t prevDirection;
	float directionalMoveCoeff;

	//Animation Section
	AnimationSet * animations;
	void updateAnimation(size_t animationNumber);
};*/
#endif