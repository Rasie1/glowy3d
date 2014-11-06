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
#include <cmath>
#include "Graphics/Layer.h"
#include "Base/EngineDirector.h"
#include "Platforms/VertexBuffer.h"

namespace glowy2d
{
	Layer * Layer::create(uint16 maxSprites)
	{
		auto ret = new Layer(maxSprites);
		ret->initBuffers();
		EngineDirector::getInstance()->add(ret);

		return ret;
	}

	Layer::Layer(uint maxSprites)
	{
		this->maxSprites = maxSprites;
		vertexCoords = new float[maxSprites * 12];
		texCoords = new float[maxSprites * 8];
		textures = new TextureAtlas(1024);
	}

	void Layer::initBuffers()
	{
		texBuffer = new VertexBuffer();
		texBuffer->bindForTextureAttrib();
		texBuffer->buffer(maxSprites * 32, texCoords);

		vertexBuffer = new VertexBuffer();
		vertexBuffer->bindForVertexAttrib();
		vertexBuffer->buffer(maxSprites * 48, vertexCoords);
	}

	Layer::~Layer()
	{
		delete vertexBuffer;
		delete texBuffer;

		delete textures;
		delete[] vertexCoords;
		delete[] texCoords;
	}

	void Layer::updateVertexBuffer()
	{
		vertexBuffer->bindForArray();
		vertexBuffer->update(0, spritesNum * 48, vertexCoords);
	};

	void Layer::updateTextureBuffer()
	{
		texBuffer->bindForArray();
		texBuffer->update(0, spritesNum * 32, texCoords);
	}

	void Layer::draw()
	{
		bindTexture();
		bindVbo();
		bindIbo();

		EngineDirector::getInstance()->draw(spritesNum * 6);
	}

	void Layer::clear()
	{
	}

	Texture * Layer::addTexture(const char * imagePath)
	{
		return addTexture(TextureData::load(imagePath));
	}

	Texture * Layer::addTexture(TextureData * imageData)
	{
		Texture * tex = textures->add(imageData);

		return tex;
	}

	Sprite * Layer::add(Texture * texture)
	{
		//Index for the start of current coords in array
		const uint vertexPos = spritesNum * 12;
		const uint texPos = spritesNum * 8;

		texture->copyTo(texCoords + texPos);
		memcpy(vertexCoords + vertexPos, Constants::quadCoords, sizeof(Constants::quadCoords));

		//Set correct size
		vertexCoords[vertexPos + 1] *= texture->size.x;//I don't know why it's x
		vertexCoords[vertexPos + 6] *= texture->size.x;
		vertexCoords[vertexPos + 7] *= texture->size.y;
		vertexCoords[vertexPos + 9] *= texture->size.x;

		Sprite * ret = new Sprite(vertexCoords + vertexPos, texCoords + texPos);
		++spritesNum;
		return ret;
	}

	Sprite * Layer::add(const char * imagePath)
	{
		Texture * tex = addTexture(imagePath);

		return add(tex);
	}

	void Layer::setShader(unsigned shared_id)
	{
	}

	void Layer::setTexture(const Tex2D& tex)
	{
		//this->texture = tex;
	}

	void Layer::bindVbo()
	{
		vertexBuffer->bindForVertexAttrib();
	}

	void Layer::bindIbo()
	{
		EngineDirector::getInstance()->indexBuffer->bindForIndices();
	}

	void Layer::bindTexture()
	{
		texBuffer->bindForTextureAttrib();

		textures->bind();
	}

	//InterfaceObject2D

	vec2 Layer::getPosition() const
	{
		return vec2(0, 0);
	}

	void Layer::setPosition(const vec2& pos)
	{
		for (uint i = 0; i < spritesNum * 12; i += 3)
		{
			vertexCoords[i] -= position.x - pos.x;
			vertexCoords[i + 1] -= position.y - pos.y;
		}
		position = pos;
	}

	void Layer::addPosition(const vec2& offset)
	{
		for (uint i = 0; i < spritesNum * 12; i += 3)
		{
			vertexCoords[i] += offset.x;
			vertexCoords[i + 1] += offset.y;
		}
	}

	float Layer::getRotation() const
	{
		return 0;
	}

	void Layer::setRotation(const float rotation)
	{
		addRotation(rotation - this->rotation);
	}

	void Layer::addRotation(const float offset)
	{
		addRotation(offset, cos(offset / 100.f), sin(offset / 100.f));
	}

	void Layer::addRotation(const float offset, const float cosr, const float sinr)
	{
		float deltaX, deltaY;

		for (uint i = 0; i < spritesNum * 12; i += 12)
		{
			deltaX = vertexCoords[i] - getOrigin().x;
			deltaY = vertexCoords[i + 1] - getOrigin().y;
			vertexCoords[i] = getOrigin().x + cosr * deltaX - sinr * deltaY;
			vertexCoords[i + 1] = getOrigin().y + sinr * deltaX + cosr * deltaY;

			deltaX = vertexCoords[i + 3] - getOrigin().x;
			deltaY = vertexCoords[i + 4] - getOrigin().y;
			vertexCoords[i + 3] = getOrigin().x + cosr * deltaX - sinr * deltaY;
			vertexCoords[i + 4] = getOrigin().y + sinr * deltaX + cosr * deltaY;

			deltaX = vertexCoords[i + 6] - getOrigin().x;
			deltaY = vertexCoords[i + 7] - getOrigin().y;
			vertexCoords[i + 6] = getOrigin().x + cosr * deltaX - sinr * deltaY;
			vertexCoords[i + 7] = getOrigin().y + sinr * deltaX + cosr * deltaY;

			deltaX = vertexCoords[i + 9] - getOrigin().x;
			deltaY = vertexCoords[i + 10] - getOrigin().y;
			vertexCoords[i + 9] = getOrigin().x + cosr * deltaX - sinr * deltaY;
			vertexCoords[i + 10] = getOrigin().y + sinr * deltaX + cosr * deltaY;
		}

		this->rotation += offset;
	}

	vec2 Layer::getScale() const
	{
		return vec2(0, 0);
	}

	void Layer::setScale(const vec2& scale)
	{
	}

	void Layer::addScale(const vec2& offset)
	{
	}

	float Layer::getScaleX() const
	{
		return 0;
	}

	void Layer::setScaleX(const float scale)
	{
	}

	void Layer::addScaleX(const float offset)
	{
	}

	float Layer::getScaleY() const
	{
		return 0;
	}

	void Layer::setScaleY(const float scale)
	{
	}

	void Layer::addScaleY(const float offset)
	{
	}

	vec2 Layer::getOrigin() const
	{
		return vec2(0, 0);
	}

	void Layer::setOrigin(const vec2& point)
	{
	}

	float Layer::getZOrder() const
	{
		return 0;
	}

	void Layer::setZOrder(const float zorder)
	{
	}

	void Layer::addZOrder(const float offset)
	{
	}
}