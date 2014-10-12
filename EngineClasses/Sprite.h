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
#include "IncludesEngine.h"
#include "InterfaceObject2D.h"
#include "TextureInfo.h"

namespace glowy2d
{
	class DLLEXPORT Sprite : public InterfaceObject2D
	{
	public:
		Sprite(float * vboPointer, float * texCoordPointer);
		~Sprite();

		bool isHidden() const;
		void setHidden(bool isHidden);

		vec2 getPosition() const;
		void setPosition(const vec2& pos);
		void addPosition(const vec2& offset);

		vec2 getOrigin() const;
		void setOrigin(const vec2& pos); //TODO

		//TODO
		vec2 getScale() const;
		void setScale(const vec2& scale);
		void addScale(const vec2& offset);

		float getScaleX() const;
		void setScaleX(const float scale);
		void addScaleX(const float offset);

		float getScaleY() const;
		void setScaleY(const float scale);
		void addScaleY(const float offset);

		//TODO
		float getRotation() const;
		void setRotation(const float rotation);
		void addRotation(const float offset);

		float getZOrder() const;
		void setZOrder(const float zorder);
		void addZOrder(const float offset);

		TextureInfo * getTexture() const;
		void setTexture(TextureInfo * texture);

	private:
		vec2 position, scale;
		float rotation;

		//Sets VBO array pointer. 
		//Useful for layered drawing to reuse the same vbo data
		void pointToVbo(float * vbo);

		//float vbo[QUAD_VERTEX_NUM];
		bool is_hidden = false;

		//Data pointers to layer array
		VertexCoords vertexCoords;
		TexCoords texCoords;
		TextureInfo * texture;

		//Utility data
		bool has_changed = true;
	};

}
