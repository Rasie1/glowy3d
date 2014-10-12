#ifndef __TEXTURE_GENERATOR_H__
#define __TEXTURE_GENERATOR_H__

#include "cocos2d.h"
#include "Libs.h"
#include "TextureInfo.h"

USING_NS_CC;

class TextureInfo;
class TexturePartInfo;

struct TexturePathEntity
{
	int layer, style, variation;

	TexturePathEntity(int layerNum, int styleNum, int variationNum)
		: layer(layerNum), style(styleNum), variation(variationNum) {}

	bool operator<(const TexturePathEntity& second) const { return layer < second.layer; }
};

class TextureGenerator : public Ref
{
public:
	static TextureGenerator * create(std::string prefix, const Size& size = Size(256, 256));
	bool init(std::string prefix, const Size& size);

	virtual TextureInfo * getTexture();

private:
	Size size;
	std::string prefixPath;
	std::vector<TexturePathEntity> textureFiles;
	TextureGenerator() {}
};

#endif