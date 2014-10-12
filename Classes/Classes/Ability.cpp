#include "Ability.h"


Ability* Ability::create(MapInfo * map, Actor * user, float delayBefore, int animationBefore, float delayAfter, int animationAfter)
{
	Ability * ref = new Ability();
	if (ref && ref->init(map, user, delayAfter, delayBefore))
	{
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

void Ability::apply(Vec2 param)
{
	if (!usable)
		return;
}

bool Ability::init(MapInfo * map, Actor * user, float delayAfter, float delayBefore)
{
	this->user = user;
	this->map = map;
	this->delayAfter = delayAfter;
	this->delayBefore = delayBefore;
	usable = true;
	return true;
}

void Ability::updateStats()
{

}

void Ability::setUsable(bool val)
{
	usable = val;
}

void Ability::applyDelayAfter()
{
	if (delayAfter > 0)
	{
		//usable = false;
		//usable = true;//TODO schedule
	}
}
//AbilityAttack

AbilityAttack* AbilityAttack::create(MapInfo * map, Actor * user)
{
	auto ref = new AbilityAttack();
	if (ref && ref->init(map, user))
	{
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

void AbilityAttack::apply(Vec2 param)
{
	if (!usable)
		return;
	for (int i = map->actors.size() - 1; i >= 0; --i)
	if (user->getPosition().getDistanceSq(map->actors.at(i)->getPosition()) < ((Creature*)user)->getAttackRangeSq() && user != map->actors.at(i))
		map->actors.at(i)->takeDamage(user, 17, DMGTYPE_DIRECT);
	applyDelayAfter();
}

bool AbilityAttack::init(MapInfo * map, Actor * user)
{
	Ability::init(map, user, 1.0f, 0.0f); //Read delay from character
	//effects.pushBack(EffectInstantDamage::create();
	return true;
}

//AbilityMoveTo

AbilityMoveTo* AbilityMoveTo::create(MapInfo * map, Actor * user)
{
	auto ref = new AbilityMoveTo();
	if (ref && ref->init(map, user))
	{
		ref->autorelease();
		return ref; 
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

void AbilityMoveTo::apply(Vec2 param)
{
	if (!usable)
		return;
	((Creature*)user)->moveTo(param);
}

bool AbilityMoveTo::init(MapInfo * map, Actor * user)
{
	Ability::init(map, user, 0.0f, 0.0f);
	return true;
}
