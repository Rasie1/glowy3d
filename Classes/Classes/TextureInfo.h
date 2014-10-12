#ifndef __TEXTURE_INFO_H__
#define __TEXTURE_INFO_H__

#include "cocos2d.h"
#include "Libs.h"
#include "TextureGenerator.h"

USING_NS_CC;

class Actor;
class TextureGenerator;

//Combine these parts with TextureInfo to generate a texture
class TexturePartInfo : public Ref
{
public:
	static TexturePartInfo * create(std::string filePath, Vec2 pos = Vec2(0, 0), Color4F color = Color4F(1.0, 1.0, 1.0, 1.0), Size size = Size(256, 256), int zOrder = 0, int transform = 0);
	bool init(std::string filePath, Vec2 pos, Color4F color, Size size, int zOrder, int transform);

	Color4F const & getColor();
	std::string const & getFilePath();
	Vec2 const & getPosition();
	Size const & getSize();
	int const & getZOrder();
	int const & getTransform();

	//Returns full copy of this TexturePartInfo with applied transformation
	TexturePartInfo * getFlipped(int transform = 1) const;
private:
	TexturePartInfo() {}
	Color4F color;
	std::string filePath;
	Vec2 pos;
	Size size;
	int zOrder;
	int transform;
};

//A texture made out of TexturePartInfo's.
class TextureInfo : public Ref
{
public:
	std::vector<TexturePartInfo*> parts;

	Texture2D * getTexture();
	bool init();

	static TextureInfo * create(TexturePartInfo * tex);
	static TextureInfo * create();
	void add(TexturePartInfo * partPack);
	void add(TextureInfo * parts);

	//Returns full copy of this TextureInfo with applied transformation
	TextureInfo * getFlipped(int transform = 1) const;
private:
	TextureInfo() {}

	Texture2D * generated;
	bool isGenerated;
};

#endif