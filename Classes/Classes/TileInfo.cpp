#include "TileInfo.h"

//TileInfo

TileInfo * TileInfo::create(TextureInfo * texture, int type)
{
	TileInfo * ret = new TileInfo();
	if (ret && ret->init(texture, type))
	{
		ret->autorelease();
		ret->retain();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool TileInfo::init(TextureInfo * texture, int type)
{
	this->type = type;
	this->tex = texture;

	return true;
}

bool TileInfo::isWalkable()
{
	return type != TILE_NONE;
}

int TileInfo::getType()
{
	return type;
}

Texture2D * TileInfo::getTexture()
{
	return tex->getTexture();
}

std::string fileOutput()
{
	return "nope";
}