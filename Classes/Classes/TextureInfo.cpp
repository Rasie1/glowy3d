#include "TextureInfo.h"

//TexturePartInfo

TexturePartInfo * TexturePartInfo::create(std::string filePath, Vec2 pos, Color4F color, Size size, int zOrder, int transform)
{
	TexturePartInfo * ret = new TexturePartInfo();
	if (ret && ret->init(filePath, pos, color, size, zOrder, transform))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool TexturePartInfo::init(std::string filePath, Vec2 pos, Color4F color, Size size, int zOrder, int transform)
{
	this->filePath = filePath;
	this->pos = pos;
	this->size = size;
	this->color = color;
	this->zOrder = zOrder;
	this->transform = transform;

	return true;
}

Color4F const & TexturePartInfo::getColor()
{
	return color;
}

std::string const & TexturePartInfo::getFilePath()
{
	return filePath;
}

Vec2 const & TexturePartInfo::getPosition()
{
	return pos;
}

Size const & TexturePartInfo::getSize()
{
	return size;
}

int const & TexturePartInfo::getZOrder()
{
	return zOrder;
}

int const & TexturePartInfo::getTransform()
{
	return transform;
}

TexturePartInfo * TexturePartInfo::getFlipped(int transform) const
{
	TexturePartInfo * ret = TexturePartInfo::create(filePath, pos, color, size, zOrder, transform);

	return ret;
}

//TextureInfo

TextureInfo * TextureInfo::create(TexturePartInfo * tex)
{
	TextureInfo * ret = new TextureInfo();
	if (ret && ret->init())
	{
		ret->autorelease();
		ret->add(tex);
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

TextureInfo * TextureInfo::create()
{
	TextureInfo * ret = new TextureInfo();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool TextureInfo::init()
{
	isGenerated = false;
	return true;
}

void TextureInfo::add(TexturePartInfo * part)
{
	parts.push_back(part);
	isGenerated = false;
}

void TextureInfo::add(TextureInfo * partsPack)
{
	int n = partsPack->parts.size();
	for (int i = 0; i < n; ++i)
		add(partsPack->parts.at(i));
	isGenerated = false;
}

Texture2D * TextureInfo::getTexture()
{
	if (!isGenerated)
	{
		generated = assembleTexture(this); 
		isGenerated = true;
	}
	return generated;
}

TextureInfo * TextureInfo::getFlipped(int transform) const
{
	TextureInfo * ret = new TextureInfo();

	int n = parts.size();
	for (int i = 0; i < n; ++i)
	{
		ret->add(parts[i]->getFlipped(transform));
	}
	return ret;
}