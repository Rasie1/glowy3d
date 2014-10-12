#include "Tileset.h"

//TypeTileset

TypeTileset * TypeTileset::create()
{
	TypeTileset * ret = new TypeTileset();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool TypeTileset::init()
{
	return 1;
}

void TypeTileset::add(TextureInfo * tex)
{
	tiles.pushBack(tex);
}

TextureInfo * TypeTileset::getRandom()
{
	return tiles.getRandomObject();
}

//Tileset

Tileset * Tileset::create()
{
	Tileset * ret = new Tileset();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

TextureInfo * Tileset::getByType(int type)
{
	CCASSERT(types[type], "No such tile in tileset");
	return types[type]->getRandom();
}

void Tileset::add(TextureInfo * tex, int type)
{
	if (!types[type])
		types[type] = TypeTileset::create();
	types[type]->add(tex);
}

bool Tileset::init()
{
	return true;
}