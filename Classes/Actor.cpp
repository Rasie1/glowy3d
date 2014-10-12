#include "stdafx.h"
#include "Actor.h"

namespace mygame
{
	bool Actor::init()
	{


		return true;
	}

	void Actor::update()
	{

	}

	bool Actor::isActive() const
	{
		return active;
	}

	void Actor::setActive(const bool value)
	{
		active = value;
	};
}