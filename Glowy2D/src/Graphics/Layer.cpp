/****************************************************************************
This file is part of glowy2d.

Copyright (c) 2015 Kvachev 'Rasie1' V. D.

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
#include "Base/System.h"
#include "Graphics/Sprite.h"
#include "Graphics/Camera.h"
#include "Graphics/Texture.h"
#include "Graphics/TextureAtlas.h"
#include "Graphics/TextureData.h"
#include "Platforms/IndexBuffer.h"
#include "Platforms/VertexInterleavedBuffer.h"
#include "Platforms/Renderer.h"


using namespace std;
namespace glowy2d
{

Layer::Layer(uint maxSprites, uint atlasSize) :
	maxSprites(maxSprites),
	vertices(new quad[maxSprites]),
	textures(new TextureAtlas(atlasSize)),
	matrix(0),
	spritesNum(0),
	zOrder(0)
{
	vertexBuffer = new VertexInterleavedBuffer(vertices, maxSprites * sizeof(quad));
	vertexBuffer->setLayoutForTextureCoords();
	vertexBuffer->setLayoutForPosition();
}

Layer::~Layer()
{
	delete vertexBuffer;
	delete textures;
	delete[] vertices;
}

void Layer::updateBuffer()
{
	vertexBuffer->bind();
	vertexBuffer->updateData(vertices, 
							 spritesNum * sizeof(quad), 
							 0);
}

void Layer::draw()
{
	System::renderer->setMatrix(matrix, System::camera->getMatrix());
	vertexBuffer->bind();
	vertexBuffer->setLayoutForTextureCoords();
	textures->bind();
	vertexBuffer->setLayoutForPosition();
	bindIbo();
	
	System::renderer->draw(spritesNum * 6);
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
	const uint texPos    = spritesNum * 8;

	vertices[spritesNum].setDefaultCoords();
	texture->copyTo(vertices + spritesNum);
	
	vertices[spritesNum].tl.position.y *= texture->size.y; // here was x
	vertices[spritesNum].br.position.x *= texture->size.x;
	vertices[spritesNum].br.position.y *= texture->size.y;
	vertices[spritesNum].bl.position.x *= texture->size.x;

	Sprite * ret = new Sprite(vertices + spritesNum);
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
	throw runtime_error("set shader is in a TODO stage");
}

void Layer::setTexture(const Tex2D& tex)
{
	throw runtime_error("set texture is in a TODO stage");
}

void Layer::bindIbo()
{
	System::indexBuffer->bind();
}

void Layer::bindBuffer()
{
	vertexBuffer->bind();
}

vec2 Layer::getPosition() const
{
	return position;
}

void Layer::setPosition(const vec2& pos)
{
	//position = pos;
	matrix[0][0] = pos.x;
	matrix[1][1] = pos.y;
}

void Layer::addPosition(const vec2& offset)
{
	matrix[0][0] += offset.x;
	matrix[1][1] += offset.y;
	//position += offset;
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
	throw runtime_error("rotation is in a TODO stage");
	rotation += offset;
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
	return zOrder;
}

void Layer::setZOrder(const float zOrder)
{
	for (uint i = 0; i < spritesNum; ++i)
	{
		vertices[i].bl.zOrder = zOrder;
		vertices[i].br.zOrder = zOrder;
		vertices[i].tl.zOrder = zOrder;
		vertices[i].tr.zOrder = zOrder;
	}
	this->zOrder = zOrder;
}

void Layer::addZOrder(const float offset)
{
	for (uint i = 0; i < spritesNum; ++i)
	{
		vertices[i].bl.zOrder += zOrder;
		vertices[i].br.zOrder += zOrder;
		vertices[i].tl.zOrder += zOrder;
		vertices[i].tr.zOrder += zOrder;
	}
	this->zOrder += zOrder;
}

}