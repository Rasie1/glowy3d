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
#include "stdafx.h"
#include "Layer.h"
#include "EngineDirector.h"

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
		textures = new TextureAtlas(512);
	}

	void Layer::initBuffers()
	{
		//tex2d = Tex2D::loadBmp("test.bmp");
		//Init texture coordinates buffer
		glGenBuffers(1, &tex_coord_id);
		glBindBuffer(GL_ARRAY_BUFFER, tex_coord_id);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glBufferData(GL_ARRAY_BUFFER, maxSprites/*spritesNum*/ * 32, texCoords, GL_DYNAMIC_DRAW);

		//Init vertex coordinates buffer
		glGenBuffers(1, &vbo_id);
		bindVbo();
		glBufferData(GL_ARRAY_BUFFER, maxSprites /*spritesNum */* 48, vertexCoords, GL_DYNAMIC_DRAW);

	}

	Layer::~Layer()
	{
		delete textures;
		delete[] vertexCoords;
		delete[] texCoords;
	}

	void Layer::updateVertexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, spritesNum * 48, vertexCoords);
	};

	void Layer::updateTextureBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, tex_coord_id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, spritesNum * 32, texCoords);
	}

	void Layer::draw()
	{
		bindTexture();
		bindVbo();
		bindIbo();

		glDrawElements(GL_TRIANGLES, spritesNum * 6, GL_UNSIGNED_SHORT, 0);
	}

	void Layer::clear()
	{

	}

	TextureInfo * Layer::addTexture(const char * imagePath)
	{
		TextureData * imageData = TextureData::load(imagePath);
		TextureInfo * tex = textures->add(imageData);

		return tex;
	}

	Sprite * Layer::add(TextureInfo * texture)
	{
		texture->copyTo(&texCoords[spritesNum * 8]);
		Sprite * ret = new Sprite(&vertexCoords[spritesNum * 12], &texCoords[spritesNum * 8]);
		++spritesNum;
		return ret;
	}

	Sprite * Layer::add(const char * imagePath)
	{
		TextureInfo * tex = addTexture(imagePath);

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
		glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	void Layer::bindIbo()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EngineDirector::getInstance()->ibo_id);
	}

	void Layer::bindTexture()
	{
		glBindBuffer(GL_ARRAY_BUFFER, tex_coord_id);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		textures->bind();
		//tex2d.bind();
	}

	//InterfaceObject2D

	vec2 Layer::getPosition() const
	{
		return vec2(0, 0);
	}

	void Layer::setPosition(const vec2& pos)
	{
		for (int i = 0; i < spritesNum * 12; i += 3)
		{
			vertexCoords[i] -= position.x - pos.x;
			vertexCoords[i + 1] -= position.y - pos.y;
		}
		position = pos;
	}

	void Layer::addPosition(const vec2& offset)
	{
		for (int i = 0; i < spritesNum * 12; i += 3)
		{
			vertexCoords[i] += offset.x;
			vertexCoords[i + 1] += offset.y;
		}
	}

	float Layer::getRotation() const
	{
		return 0;
	}

	void Layer::setRotation(const float pos)
	{

	}

	void Layer::addRotation(const float offset)
	{

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