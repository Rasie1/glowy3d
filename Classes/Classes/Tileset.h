#ifndef __TILESET_H__
#define __TILESET_H__

#include "cocos2d.h"
#include "Libs.h"
#include "TextureInfo.h"

USING_NS_CC;

class Actor;
class TextureInfo;

//A set of texture variations for the same tile type
class TypeTileset : public Ref
{
public:
	static TypeTileset * create();
	bool init();

	void add(TextureInfo * tex);
	TextureInfo * getRandom();
private:
	TypeTileset() {}
	Vector<TextureInfo*> tiles;
};

//A set of visual textures for the map
class Tileset : public Ref
{
public:
	static Tileset * create();
	bool init();
	
	void add(TextureInfo * tex, int type);
	TextureInfo * getByType(int type);
private:
	std::map<int, TypeTileset*> types;
	Tileset() {}
};

#endif