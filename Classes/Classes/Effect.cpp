#include "Effect.h"

Effect* Effect::create(Actor * actor)
{
	auto ref = new Effect();
	if (ref && ref->init(actor))
	{
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

bool Effect::apply()
{
	return true;
}

bool Effect::init(Actor * actor)
{
	target = actor;
	return true;
}

//EffectInstantDamage

EffectInstantDamage* EffectInstantDamage::create(Actor * actor, int damage)
{
	auto ref = new EffectInstantDamage();
	if (ref && ref->init(actor, damage))
	{
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

bool EffectInstantDamage::apply()
{
	target->setHealth(target->getHealth() - dmg);
	return true;
}

bool EffectInstantDamage::init(Actor * actor, int damage)
{
	Effect::init(actor);
	dmg = damage;
	return true;
}

//EffectMoveTo

EffectMoveTo* EffectMoveTo::create(Actor * actor, float speed, Vec2 pos)
{
	auto ref = new EffectMoveTo();
	if (ref && ref->init(actor, speed, pos))
	{
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

bool EffectMoveTo::apply()
{
	target->setPosition(target->getPosition() + delta);
	return isDone();
}

bool EffectMoveTo::init(Actor * actor, float speed, Vec2 pos)
{
	Effect::init(actor);
	this->pos = pos;
	this->speed = speed;
	
	delta = scaleTo(pos - actor->getPosition(), speed);
	return true;
}

bool EffectMoveTo::isDone()
{
	return target->getPosition().getDistanceSq(pos) < 100;
}