#pragma once
#include "g2dMath.h"
#include "graphics/Texture.h"
#include "graphics/TextureData.h"
#include "platforms/Tex2D.h"

namespace glowy3d
{
	
struct AtlasNode
{
	AtlasNode(usrect rectangle) : 
        r(rectangle) {}

	AtlasNode* child[2];
	usrect r;
	TextureData* data;
	bool closed = false;
	bool leaf 	= true;
	bool cutx 	= false;
	AtlasNode* insert(TextureData* tex);
};

class TextureAtlas
{
public:
	//A texture atlas. Use add() to add textures
	//to atlas and then generate() to assemble them and
	//prepare for drawing. add() returns a Texture 
	//object that is passed to sprites.
	TextureAtlas(unsigned short maxSize);
	~TextureAtlas();

	//When you finished to add your images to the atlas,
	//call generate() to get them ready for drawing
	Texture* add(TextureData* data);

	void bind();

private:
	AtlasNode* tree;
	TextureData* data;
	Tex2D tex;
};

}
