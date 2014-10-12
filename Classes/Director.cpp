#include "stdafx.h"
#include "Director.h"

namespace mygame
{
	bool Director::singletonInitialised;
	Director Director::singletonInstance;

	bool Director::init()
	{

		return true;
	}

	Director::Director()
	{
		singletonInitialised = true;
	}

	Director::~Director()
	{
		singletonInitialised = false;
	}


	Director * Director::getInstance()
	{
		return singletonInitialised ? &singletonInstance : 0;
	}

	World * Director::getWorld() const
	{
		return world;
	}
}