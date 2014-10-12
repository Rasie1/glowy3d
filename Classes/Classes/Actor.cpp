#include "Actor.h"

Actor* Actor::create(const Vec2& pos, MapInfo * map)
{
	auto ref = new (std::nothrow) Actor();
	if (ref && ref->init(pos, map))
	{
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

bool Actor::init(const Vec2& pos, MapInfo * map)
{
	Sprite::init();
	this->map = map;
	//this->setTexture("items/potion_bottle_0.png");
	//this->setGLProgram(GLProgram::createWithFilenames("Shaders/colorize_saturation.vsh", "Shaders/colorize_saturation.fsh"));
	//this->getGLProgramState()->setUniformVec4("u_rgbs", Vec4(1.0f, 0.0f, 0.0f, 12.0f));
	setPosition(pos);
	health = 1;
	radius = 32;
	selectable = true;
	sleeping = true;
	onMouseDown = nullptr;
	teamNumber = TEAM_NEUTRAL;

	return true;
}

void Actor::actTenth()
{
	applyEffects();
	if (health < 1)
		die();

	/*updateCollisionMap();*/
	//Next animation frame
	//setTexture(animation->getNextFrame()->getTexture());
}

void Actor::die()
{
	setVisible(false);
	//level->overlay->remove(onMouseDown);
}

void Actor::useAbility(int abilityNumber, Vec2 param)
{
	abilities.at(abilityNumber)->apply(param);
}

Ability * Actor::getAbility(int abilityNumber)
{
	return abilities.at(abilityNumber);
}

void Actor::applyEffects()
{
	for (int i = effects.size() - 1; i >= 0; --i)
	{
		if (effects.at(i)->apply())
		{
			effects.erase(i);
		}
	}
}

void Actor::addEffect(Effect * effect)
{
	effects.pushBack(effect);
}

bool Actor::isTouched(const Vec2& byThis)
{
	return getPosition().distanceSquared(byThis) <= radius * radius;
}

void Actor::act(float timeCoefficient)
{
}

void Actor::takeDamage(Actor * user, int damage, int type)
{
	addEffect(EffectInstantDamage::create(this, damage));
}

void Actor::setAnimation(AAnimation * animation)
{
	this->animation = animation;
}

int Actor::getHealth()
{
	return health;
}

int Actor::getRadius()
{
	return radius;
}

bool Actor::isSleeping()
{
	return sleeping;
}

void Actor::setHealth(int health)
{
	this->health = health;
}

void Actor::setSleeping(bool is)
{
	sleeping = is;
}

bool Actor::isSelectable()
{
	return selectable;
}

void Actor::updateCollisionMap()
{
}

bool Actor::isAlly(int teamNum)
{
	if (teamNum == TEAM_NEUTRAL || teamNum == teamNumber)
		return true;
	return false;
}

int Actor::getTeam()
{
	return teamNumber;
}

void Actor::dropItem(Item * item)
{
	auto f = itemsEquipped.getIndex(item);
	if (f != UINT_MAX)
	{
		map->addActor(ItemActor::create(item, getPosition(), map));
		itemsEquipped.erase(f);
		return;
	}
	f = itemsInventory.getIndex(item);
	if (f != UINT_MAX)
	{
		map->addActor(ItemActor::create(item, getPosition(), map));
		itemsInventory.erase(f);
	}
}

void Actor::addItem(Item * item)
{
	itemsInventory.pushBack(item);
}

//ItemActor

ItemActor* ItemActor::create(Item * item, const Vec2& pos, MapInfo * map)
{
	auto ref = new ItemActor();
	if (ref && ref->init(item, pos, map))
	{
		ref->autorelease();
		return ref;
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

bool ItemActor::init(Item * item, const Vec2& pos, MapInfo * map)
{
	Actor::init(pos, map);
	this->item = item;
	setTexture("items/potion_bottle_0.png");
	//this->setGLProgram(GLProgram::createWithFilenames("Shaders/colorize_saturation.vsh", "Shaders/colorize_saturation.fsh"));
	//this->getGLProgramState()->setUniformVec4("u_rgbs", Vec4(1.0f, 0.0f, 0.0f, 12.0f));
	health = 1;
	radius = 32;
	selectable = true;
	sleeping = true;
	onMouseDown = nullptr;
	teamNumber = TEAM_NEUTRAL;

	return true;
}