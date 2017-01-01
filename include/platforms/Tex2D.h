#pragma once
#include "g2dMath.h"

namespace glowy3d
{

class TextureData;
struct Tex2D
{
public:
	void bind();

	Tex2D(TextureData* data);

	Tex2D(const char *filename);
	Tex2D() {}
	~Tex2D();

	//Modifies texture data by replacing selected pixels
	void pixelsReplace(TextureData* data, usvec2 offset);

	static Tex2D load(const ubyte *data, const usvec2& size);

	//Deletes the texture from memory
	void release();

private:
	uint id, uniform_id;
	usvec2 size;
};

}
