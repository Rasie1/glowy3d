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
#include "Graphics/Layer.h"
#include "Base/EngineDirector.h"
#include <cmath>

namespace glowy2d
{
	Layer * Layer::create(unsigned short maxSprites)
	{
		auto ret = new Layer(maxSprites);
		ret->initBuffers();
		EngineDirector::getInstance()->add(ret);

		return ret;
	}

	Layer::Layer(unsigned maxSprites)
	{
		this->maxSprites = maxSprites;
		vertexCoords = new float[maxSprites * 12];
		texCoords = new float[maxSprites * 8];
		textures = new TextureAtlas(1024);
	}

	void Layer::initBuffers()
	{
#ifdef R_OPENGL
		//Init texture coordinates buffer
		glGenBuffers(1, &tex_coord_id);
		glBindBuffer(GL_ARRAY_BUFFER, tex_coord_id);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBufferData(GL_ARRAY_BUFFER, maxSprites/*spritesNum*/ * 32, texCoords, GL_DYNAMIC_DRAW);

		//Init vertex coordinates buffer
		glGenBuffers(1, &vbo_id);
		bindVbo();
		glBufferData(GL_ARRAY_BUFFER, maxSprites /*spritesNum */ * 48, vertexCoords, GL_DYNAMIC_DRAW);
#else //ifdef R_DIRECT3D

#endif //R_OPENGL
	}

	Layer::~Layer()
	{
		delete textures;
		delete[] vertexCoords;
		delete[] texCoords;
	}

	void Layer::updateVertexBuffer()
	{
#ifdef R_OPENGL
		glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, spritesNum * 48, vertexCoords);
#else //ifdef R_DIRECT3D

#endif //R_OPENGL
	};

	void Layer::updateTextureBuffer()
	{
#ifdef R_OPENGL
		glBindBuffer(GL_ARRAY_BUFFER, tex_coord_id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, spritesNum * 32, texCoords);
#else //ifdef R_DIRECT3D

#endif //R_OPENGL
	}

	void Layer::draw()
	{
#ifdef R_OPENGL
		bindTexture();
		bindVbo();
		bindIbo();

		glDrawElements(GL_TRIANGLES, spritesNum * 6, GL_UNSIGNED_INT, 0);
#else //ifdef R_DIRECT3D

#endif //R_OPENGL
	}

	void Layer::clear()
	{
	}

	Texture * Layer::addTexture(const char * imagePath)
	{
		TextureData * imageData = TextureData::load(imagePath);
		Texture * tex = textures->add(imageData);

		return tex;
	}

	Sprite * Layer::add(Texture * texture)
	{
		/*texture->copyTo(&texCoords[spritesNum * 8]);

		memcpy(&vertexCoords[spritesNum * 12], Constants::quadCoords, sizeof(Constants::quadCoords));
		for (int i = 0; i < 12; ++i)
		vertexCoords[i ] *= 256.f;

		Sprite * ret = new Sprite(&vertexCoords[spritesNum * 12], &texCoords[spritesNum * 8]);
		++spritesNum;
		return ret;
		*/

		//Index for the start of current coords in array
		const unsigned vertexPos = spritesNum * 12;
		const unsigned texPos = spritesNum * 8;

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
#ifdef R_OPENGL
		glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
#else //ifdef R_DIRECT3D

#endif //R_OPENGL
	}

	void Layer::bindIbo()
	{
#ifdef R_OPENGL
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EngineDirector::getInstance()->ibo_id);
#else //ifdef R_DIRECT3D

#endif //R_OPENGL
	}

	void Layer::bindTexture()
	{
#ifdef R_OPENGL
		glBindBuffer(GL_ARRAY_BUFFER, tex_coord_id);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
#else //ifdef R_DIRECT3D

#endif //R_OPENGL

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