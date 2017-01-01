#include "graphics/Sprite.h"
#include "graphics/Texture.h"

using namespace std;

namespace glowy3d
{

Sprite::Sprite(quad *vboPointer)
{
	coords = vboPointer;
	is_hidden = false;
	has_changed = false;
}

Sprite::~Sprite()
{

}

bool Sprite::isHidden() const
{
	return is_hidden;
}

void Sprite::setHidden(bool isHidden)
{
	is_hidden = isHidden;
}

vec2 Sprite::getPosition() const
{
	return position;
}

void Sprite::setPosition(const vec2& pos)
{
	coords->tl.position -= position - pos;
	coords->tr.position -= position - pos;
	coords->br.position -= position - pos;
	coords->bl.position -= position - pos;
	position = pos;

	has_changed = true;
}

void Sprite::addPosition(const vec2& offset)
{
	addOrigin(offset);

	coords->tl.position += offset;
	coords->tr.position += offset;
	coords->br.position += offset;
	coords->bl.position += offset;

	has_changed = true;
}

vec2 Sprite::getScale() const
{
	return scale;
}

void Sprite::setScale(const vec2& scale)
{

}

void Sprite::addScale(const vec2& offset)
{

}

vec2 Sprite::getOrigin() const
{
	return scale;
}

void Sprite::setOrigin(const vec2& pos)
{
	origin = pos;
}

void Sprite::addOrigin(const vec2& offset)
{
	origin += offset;
}

float Sprite::getScaleX() const
{
	return scale.x;
}

void Sprite::setScaleX(const float scale)
{

}

void Sprite::addScaleX(const float offset)
{

}

float Sprite::getScaleY() const
{
	return scale.y;
}

void Sprite::setScaleY(const float scale)
{

}

void Sprite::addScaleY(const float offset)
{

}

float Sprite::getRotation() const
{
	return rotation;
}

void Sprite::setRotation(const float rotation)
{
	addRotation(rotation - this->rotation);
}

void Sprite::addRotation(const float offset)
{
	this->rotation += offset;

	auto cosr = cos(offset / 100.f);
	auto sinr = sin(offset / 100.f);

	/*float deltaX = vertexCoords[0] - getOrigin().x;
	float deltaY = vertexCoords[1] - getOrigin().y;
	vertexCoords[0] = getOrigin().x + cosr * deltaX - sinr * deltaY;
	vertexCoords[1] = getOrigin().y + sinr * deltaX + cosr * deltaY;

	deltaX = vertexCoords[3] - getOrigin().x;
	deltaY = vertexCoords[4] - getOrigin().y;
	vertexCoords[3] = getOrigin().x + cosr * deltaX - sinr * deltaY;
	vertexCoords[4] = getOrigin().y + sinr * deltaX + cosr * deltaY;

	deltaX = vertexCoords[6] - getOrigin().x;
	deltaY = vertexCoords[7] - getOrigin().y;
	vertexCoords[6] = getOrigin().x + cosr * deltaX - sinr * deltaY;
	vertexCoords[7] = getOrigin().y + sinr * deltaX + cosr * deltaY;

	deltaX = vertexCoords[9] - getOrigin().x;
	deltaY = vertexCoords[10] - getOrigin().y;
	vertexCoords[9] = getOrigin().x + cosr * deltaX - sinr * deltaY;
	vertexCoords[10] = getOrigin().y + sinr * deltaX + cosr * deltaY;*/
}

float Sprite::getZOrder() const
{
	return coords->tl.z();
}

void Sprite::setZOrder(const float zorder)
{
	coords->tl.zOrder = zorder;
	coords->tr.zOrder = zorder;
	coords->br.zOrder = zorder;
	coords->bl.zOrder = zorder;
}

void Sprite::addZOrder(const float offset)
{
	coords->tl.zOrder += offset;
	coords->tr.zOrder += offset;
	coords->br.zOrder += offset;
	coords->bl.zOrder += offset;
}

Texture* Sprite::getTexture() const
{
	return texture;
}

void Sprite::setTexture(Texture* texture)
{
	this->texture = texture;
	texture->copyTo(coords);
}
	
}
