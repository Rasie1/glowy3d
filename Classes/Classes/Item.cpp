#include "Item.h"

Item * Item::create()
{
	auto ref = new Item();
	if (ref && ref->init())
	{
		ref->autorelease();
		return ref; 
	}
	CC_SAFE_DELETE(ref);
	return nullptr;
}

bool Item::init()
{

	return true;
}