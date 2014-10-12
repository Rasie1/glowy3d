#ifndef __TILESET_GENERATOR_H__
#define __TILESET_GENERATOR_H__

#include "cocos2d.h"
#include "Libs.h"
#include "TextureInfo.h"
#include "TileInfo.h"
#include "Tileset.h"

USING_NS_CC;

class Actor;
class TextureInfo;
class TextureGenerator;
class Tileset;
class TypeTileset;

class TilesetGenerator : public Ref
{
public:
	static TilesetGenerator * create();
	bool init();

	virtual Tileset * getTileset();

private:
	TilesetGenerator() {}
};

#endif