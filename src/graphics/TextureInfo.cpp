#include "graphics/TextureInfo.h"

using namespace std;

namespace glowy3d
{

TextureInfo::TextureInfo()
{
}

TextureInfo::~TextureInfo()
{
}

void TextureInfo::addPart(TexturePartInfo* part)
{
	parts.push_back(part);

	if (isGenerated)
	{
		isGenerated = false;
		delete generated;
	}
}

TextureData* TextureInfo::getTextureData()
{
	if (!isGenerated)
		generate();
	return generated;
}

void TextureInfo::generate()
{
	isGenerated = true;
}

}
