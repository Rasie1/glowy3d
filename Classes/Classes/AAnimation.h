#ifndef __AANIMATION_H__
#define __AANIMATION_H__

#include "cocos2d.h"
#include "Actor.h"
#include "Creature.h"
#include "Player.h"

USING_NS_CC;

class Actor;
class TextureInfo;
class World;
class Creature;
class Player;

enum AnimationNames
{
	ANIMATION_NONE,
	ANIMATION_IDLE,
	ANIMATION_IDLE_N,
	ANIMATION_IDLE_NE,
	ANIMATION_IDLE_E,
	ANIMATION_IDLE_SE,
	ANIMATION_IDLE_S,
	ANIMATION_IDLE_SW,
	ANIMATION_IDLE_W,
	ANIMATION_IDLE_NW,
	ANIMATION_RUN,
	ANIMATION_RUN_N,
	ANIMATION_RUN_NE,
	ANIMATION_RUN_E,
	ANIMATION_RUN_SE,
	ANIMATION_RUN_S,
	ANIMATION_RUN_SW,
	ANIMATION_RUN_W,
	ANIMATION_RUN_NW,
	ANIMATION_ATTACK,
	ANIMATION_ATTACK_N,
	ANIMATION_ATTACK_NE,
	ANIMATION_ATTACK_E,
	ANIMATION_ATTACK_SE,
	ANIMATION_ATTACK_S,
	ANIMATION_ATTACK_SW,
	ANIMATION_ATTACK_W,
	ANIMATION_ATTACK_NW,

	ANIMATIONS_AMOUNT
};

class AAnimation : public Ref
{
public:
	static AAnimation * create();
	bool init();
	void addFrame(TextureInfo * texture);

	TextureInfo * getNextFrame();
	void setFrame(int frame);
private:
	Vector<TextureInfo*> frames; //or Texture2D?
	int iterator, framesSize;
};

class AnimationSet : public Ref
{
public:
	static AnimationSet * create();
	bool init();

	Action * animations[ANIMATIONS_AMOUNT];
private:
	~AnimationSet();
};

#endif