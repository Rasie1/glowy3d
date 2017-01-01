#pragma once
#include "g2dMath.h"
#include "math/quad.h"

namespace glowy3d
{

//Texture class for passing between the sprites in the SAME layer
//You should get those from Layer::addTexture
class Texture
{
public:
	const vec2 *getCoords() const;
	usvec2 getSize() const;

	friend class Layer;
	friend class TextureAtlas;
	friend class Sprite;
	
private:
	void copyTo(quad* destination);
	
	usvec2 size;
	vec2 coords[4];
};

}
