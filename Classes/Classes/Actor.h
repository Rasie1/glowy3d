#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"
#include "MapInfo.h"
#include "Ability.h"
#include "Effect.h"
#include "Libs.h"
#include "AAnimation.h"
#include "InterfaceBase.h"
#include "Item.h"
#include "MapPath.h"
USING_NS_CC;

class World;
class Ability;
class Effect;
class AAnimation;
class InterfacePart;
class MapPath;
class MapInfo;
class Item;
class AnimationSet;
class Pathfinder;

//Basic actor with health and radius
class Actor : public Sprite
{
public:
	static Actor * create(const Vec2& pos, MapInfo * map);
	virtual bool init(const Vec2& pos, MapInfo * map);


	//returns true if byThis is inside Actor's radius
	bool isTouched(const Vec2& byThis);
	//Returns true if it should be selected when hovered by mouse, etc
	bool isSelectable();
	bool isSleeping();
	//called every frame
	virtual void act(float timeCoefficient);
	//called ten times per second
	virtual void actTenth();

	virtual void die();

	void useAbility(int abilityNumber, Vec2 param = Vec2(0, 0));
	//void useAbility(Ability * ability, Vec2 param = Vec2(0, 0));
	Ability * getAbility(int abilityNumber);

	void setHealth(int health);
	void setSleeping(bool is);
	int getHealth();
	int getRadius();

	void addEffect(Effect * effect);
	void takeDamage(Actor * user, int damage, int type = 0);

	void setAnimation(AAnimation * animation);

	InterfacePart * onMouseDown;
	MapInfo * map;

	//About teams
	int getTeam();
	bool isAlly(int teamNum);

	//About items
	Vector<Item*> itemsEquipped;
	Vector<Item*> itemsInventory;
protected:
	Actor() {}

	void dropItem(Item * item);
	void addItem(Item * item);

	Vector<Effect*> effects;
	Vector<Ability*> abilities;
	Vector<AAnimation*> animations;

	int health, radius;
	bool selectable, sleeping;

	//Vector<Ability*> orders;
	//bool isActing

	AAnimation * animation;
	void applyEffects();
	virtual void updateCollisionMap();

	int teamNumber;
};

//Item actor class for placing items on ground
class ItemActor : public Actor
{
public:
	static ItemActor * create(Item * item, const Vec2& pos, MapInfo * map);
	bool init(Item * item, const Vec2& pos, MapInfo * map);

	Item * item;
private:
	MapInfo * map;

	ItemActor() {}
};


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
	bool shouldUpdatePath;

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
};


class Player : public Creature
{
public:
	static Player * create(const Vec2& pos, MapInfo * map);
	virtual bool init(const Vec2& pos, MapInfo * map);

protected:
	Player() {}
};

#endif