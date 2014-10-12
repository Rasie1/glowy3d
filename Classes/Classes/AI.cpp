#include "AI.h"

//AIStatePart

AIStatePart * AIStatePart::create(Creature * creature)
{
	AIStatePart *ret = new AIStatePart();
	if (ret && ret->init(creature))
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool AIStatePart::init(Creature * creature)
{
	this->creature = creature;

	return true;
}

void AIStatePart::apply()
{

}

//AIStatePartAttackMove

AIStatePartAttackMove * AIStatePartAttackMove::create(Creature * creature)
{
	AIStatePartAttackMove *ret = new AIStatePartAttackMove();
	if (ret && ret->init(creature))
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool AIStatePartAttackMove::init(Creature * creature)
{
	AIStatePart::init(creature);

	return true;
}

void AIStatePartAttackMove::apply()
{

}

void AIStatePartAttackMove::searchForTarget()
{
	int newDist, minDist;
	for (int i = creature->map->actors.size(); i >= 0; --i)
	if (!creature->map->actors.at(i)->isSleeping())
	{
		newDist = creature->getPosition().getDistanceSq(creature->map->actors.at(i)->getPosition());
		if (minDist > newDist && creature->isAlly(creature->map->actors.at(i)->getTeam()))
		{
			minDist = newDist;
			target = creature->map->actors.at(i);
		}
	}
}

void AIStatePartAttackMove::attackTarget()
{

}
//AIState

AIState * AIState::create(Creature * creature)
{
	AIState *ret = new AIState();
	if (ret && ret->init(creature))
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool AIState::init(Creature * creature)
{
	this->creature = creature;

	return true;
}

void AIState::apply()
{
	for (int i = parts.size() - 1; i >= 0; --i)
		parts[i]->apply();
}


//AIStateFight

AIStateFight * AIStateFight::create(Creature * creature)
{
	AIStateFight *ret = new AIStateFight();
	if (ret && ret->init(creature))
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool AIStateFight::init(Creature * creature)
{
	AIState::init(creature);

	return true;
}

//AI

AI * AI::create(Creature * creature)
{
	AI *ret = new AI();
	if (ret && ret->init(creature))
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool AI::init(Creature * creature)
{
	this->creature = creature;

	states[AI_STATE_FIGHT] = AIStateFight::create(creature);
	states[AI_STATE_STANDBY] = AIState::create(creature);

	return true;
}

int AI::getState()
{
	return stateNumber;
}

void AI::setState(int number)
{
	stateNumber = number;
}

void AI::apply()
{
	states[stateNumber]->apply();
}