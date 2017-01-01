#include "graphics/TexturePartInfo.h"

using namespace std;

namespace glowy3d
{

TexturePartInfo::TexturePartInfo(const std::string& path, const rect& rectangle) : 
	path(path), 
	rectangle(rectangle)
{
}

TexturePartInfo::~TexturePartInfo()
{
}

const rect& TexturePartInfo::getRect() const
{
	return rectangle;
}

void TexturePartInfo::setRect(const rect& newRect)
{
	rectangle = newRect;
}

const std::string& TexturePartInfo::getPath() const
{
	return path;
}

void TexturePartInfo::setPath(const std::string& newPath)
{
	path = newPath;
}

}
