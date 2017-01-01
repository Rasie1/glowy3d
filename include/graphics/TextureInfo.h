#pragma once
#include <vector>
#include "graphics/TextureData.h"
#include "graphics/TexturePartInfo.h"

//TODO
//Conversion to TextureData
//-add colors, hsb, shaders, rotation

namespace glowy3d
{

class TextureInfo
{
public:
	//Represents a single texture frame composed of TexturePartInfo's
	TextureInfo();
	~TextureInfo();

	void addPart(TexturePartInfo* part);

	TextureData* getTextureData();
	
private:
	std::vector<TexturePartInfo*> parts;

	bool isGenerated = false;
	TextureData* generated;

	void generate();
};
	
}
