#include "TextureGenerator.h"
#include "FileOperation.h"
#include <algorithm>

//TextureGenerator

TextureGenerator * TextureGenerator::create(std::string prefix, const Size& size)
{
	TextureGenerator * ret = new TextureGenerator();
	if (ret && ret->init(prefix, size))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}


bool TextureGenerator::init(std::string prefix, const Size& size)
{
	this->size = size;
	this->prefixPath = prefix;
	std::string dir = prefix;
	for (int i = dir.size() - 1; i >= 0; --i)
	{
		if (dir[i] == '\\')
		{
			prefix = dir.substr(i + 1, dir.size() - 1);
			dir.resize(i);
			break;
		}
	}

	std::vector<std::string> directoryDirty = FileOperation::listFilesInDirectory(dir);


	//Cut off unrelated files and form textureFiles array
	int prefixEnd = prefix.size();
	int item1, item2;
	char delim = '_';
	std::string item;

	int n = directoryDirty.size();

	for (int i = 0; i < n; i++)
	{
		if (directoryDirty[i].substr(0, prefixEnd) == prefix)
		{
			//We need to parse each string for LAYER and STYPE
			std::stringstream ss(directoryDirty[i]);
			std::getline(ss, item, delim); //Skip first word
			std::getline(ss, item, delim);
			item1 = std::stoi(item);
			std::getline(ss, item, delim);
			item2 = std::stoi(item.substr(0, item.size() - 4)); //Add style number (cut off ".png")

			auto entity = TexturePathEntity(item1, item2, 0);
			textureFiles.push_back(entity);
		}
	}

	std::sort(textureFiles.begin(), textureFiles.end()); //Most times, this will be a worst case for
														//quicksort, so it would work nicer with another algorithm

	return true;
}

TextureInfo * TextureGenerator::getTexture()
{
	auto tex = TextureInfo::create();

	int n = textureFiles.size();
	int currentLayer = textureFiles[0].layer;
	int currentLayerIndex = 0;
	int i = 0;
	int randomStyle;
	TexturePartInfo * part;
	std::string texturePath;

	while (++i)
	{
		if (i == n || currentLayer != textureFiles[i].layer)
		{
			randomStyle = rand() % (i - currentLayerIndex) + currentLayerIndex;
			texturePath = prefixPath + '_' + std::to_string(currentLayer) + '_' + std::to_string(textureFiles[randomStyle].style) + ".png";
			auto randomColor = Color4F(float(rand() % 256) / 255, float(rand() % 256) / 255, float(rand() % 256) / 255, 1.0f);

			part = TexturePartInfo::create(texturePath, Vec2(0, 0), randomColor, size, 0);
			tex->add(part);

			if (i == n)
				break;

			currentLayer = textureFiles[i].layer;
			currentLayerIndex = i;
		}
	}

	return tex;
}