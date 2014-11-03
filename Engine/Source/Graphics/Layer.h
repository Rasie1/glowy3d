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
#pragma once
#include "Base/IncludesEngine.h"
#include "Graphics/Sprite.h"
#include "Graphics/InterfaceDrawable.h"
#include "Graphics/InterfaceObject2D.h"
#include "Graphics/Texture.h"
#include "Graphics/TextureAtlas.h"
#include "Graphics/Tex2D.h"

namespace glowy2d
{
	class DLLEXPORT Layer : public InterfaceObject2D
	{
	public:
		//A main drawing unit: add your sprites here to draw them.
		//-maxSprites: maximum amount of sprites you may have; (TODO: remove limits)
		//
		static Layer * create(unsigned short maxSprites);
		//Use Layer::create() for convenience. If you want to use
		//it manually, call initBuffers() after constructing, and
		//call draw() everytime you want to draw.
		Layer(unsigned maxSprites);
		~Layer();
		void initBuffers();
		
		//Sends vertex data to the driver. Use it before draw()
		//if you had changed position of at least one sprite
		void updateVertexBuffer();
		//Sends texture data to the driver. Use it before draw()
		//if you had changed texture coordinates of sprite
		void updateTextureBuffer();
		//Reassembles texture atlas and sends it to driver. Use
		//it if you have added sprites with different Texture's
		void updateTexture();
		//Does all necessary things to draw sprites that are
		//currently added to layer before update() was called
		//If you had changed position of at least one sprite
		//since last draw() call, use updateBuffer() at first
		void draw();
		//Clears everything in the layer and releases all the
		//buffers and texture. Called on destruction
		void clear();
		
		//Adds new component to the layer and returns Sprite
		//object that can be modified
		//-TexCoords version: add sprite with existing texture
		Sprite * add(Texture * texture);
		//Adds new component to the layer and returns Sprite
		//object that can be modified
		//-Adds new texture to layer altas with image
		Sprite * add(const char * imagePath);
		Texture * addTexture(const char * imagePath);
		
		void setShader(unsigned shader_id);
		void setTexture(const Tex2D& tex);


		//Positioning stuff - InterfaceObject2D
		vec2 getPosition() const;
		void setPosition(const vec2& pos);
		void addPosition(const vec2& offset);

		float getRotation() const;
		void setRotation(const float rotation);
		void addRotation(const float offset);

		vec2 getScale() const;
		void setScale(const vec2& scale);
		void addScale(const vec2& offset);

		float getScaleX() const;
		void setScaleX(const float scale);
		void addScaleX(const float offset);

		float getScaleY() const;
		void setScaleY(const float scale);
		void addScaleY(const float offset);

		vec2 getOrigin() const;
		void setOrigin(const vec2& point);

		float getZOrder() const;
		void setZOrder(const float zorder);
		void addZOrder(const float offset);

	private:
		//OpenGL data
		unsigned vbo_id, tex_coord_id;

		//Vertex data
		float * vertexCoords;
		float * texCoords;

		//Object2D data
		vec2 position;
		float rotation;

		//Child sprites array
		//Sprite ** sprites;
		unsigned spritesNum;
		unsigned maxSprites;

		//OpenGL helper functions
		void bindVbo();
		void bindIbo();
		void bindTexture();
		void addRotation(const float offset, const float cosr, const float sinr);
		
		TextureAtlas * textures;

		Tex2D tex2d;
	};

}