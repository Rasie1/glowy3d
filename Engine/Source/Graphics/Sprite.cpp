/****************************************************************************
This file is part of glowy2d.

Copyright (c) 2014 Kvachev 'Rasie1' V. D.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "epc.h"
#include "Graphics/Sprite.h"

namespace glowy2d
{
	Sprite::Sprite(VertexCoords vboPointer, TexCoords texCoordPointer)
	{
		vertexCoords = vboPointer;
		texCoords = texCoordPointer;
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
		vertexCoords[0] -= position.x - pos.x;
		vertexCoords[1] -= position.y - pos.y;
		vertexCoords[3] -= position.x - pos.x;
		vertexCoords[4] -= position.y - pos.y;
		vertexCoords[6] -= position.x - pos.x;
		vertexCoords[7] -= position.y - pos.y;
		vertexCoords[9] -= position.x - pos.x;
		vertexCoords[10] -= position.y - pos.y;
		
		position = pos;

		has_changed = true;
	}

	void Sprite::addPosition(const vec2& offset)
	{
		addOrigin(offset);

		vertexCoords[0] += offset.x;
		vertexCoords[1] += offset.y;
		vertexCoords[3] += offset.x;
		vertexCoords[4] += offset.y;
		vertexCoords[6] += offset.x;
		vertexCoords[7] += offset.y;
		vertexCoords[9] += offset.x;
		vertexCoords[10] += offset.y;

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

		float deltaX = vertexCoords[0] - getOrigin().x;
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
		vertexCoords[10] = getOrigin().y + sinr * deltaX + cosr * deltaY;

	}

	float Sprite::getZOrder() const
	{
		return vertexCoords[2];
	}

	void Sprite::setZOrder(const float zorder)
	{
		vertexCoords[2] = zorder;
		vertexCoords[5] = zorder;
		vertexCoords[8] = zorder;
		vertexCoords[11] = zorder;
	}

	void Sprite::addZOrder(const float offset)
	{
		vertexCoords[2] += offset;
		vertexCoords[5] += offset;
		vertexCoords[8] += offset;
		vertexCoords[11] += offset;
	}
	
	Texture * Sprite::getTexture() const
	{
		return texture;
	}

	void Sprite::setTexture(Texture * texture)
	{
		this->texture = texture;
		texture->copyTo(texCoords);
	}
}