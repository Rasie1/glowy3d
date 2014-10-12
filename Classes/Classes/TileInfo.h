#ifndef __TILE_INFO_H__
#define __TILE_INFO_H__

#include "cocos2d.h"
#include "Libs.h"
#include "TextureInfo.h"

USING_NS_CC;

class Actor;
class TextureInfo;
class TextureGenerator;

//Main tile class
class TileInfo : public Ref
{
public:
	static TileInfo * create(TextureInfo * texture, int type);
	bool init(TextureInfo * texture, int type);
	int getType();
	Texture2D * getTexture();
	//std::vector<Actor*> actors;

	bool isWalkable();

	std::string fileOutput();
private:
	int type;
	TextureInfo * tex;
	TileInfo() {}
};

#endif