#include "graphics/Texture.h"
#include "base/System.h"

using namespace std;

namespace glowy3d
{

void Texture::copyTo(quad* destination)
{
	destination->tl.texture = coords[0];
	destination->tr.texture = coords[1];
	destination->br.texture = coords[2];
	destination->bl.texture = coords[3];
}

const vec2 *Texture::getCoords() const
{
	return coords;
}

usvec2 Texture::getSize() const
{
	return size;
}

}
