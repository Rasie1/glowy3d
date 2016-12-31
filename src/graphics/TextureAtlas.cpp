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
#include "Graphics/TextureAtlas.h"
#include "Base/System.h"

#define MAX_POSSIBLE_GAP 10

namespace glowy2d
{

TextureAtlas::TextureAtlas(unsigned short maxSize) : 
	tex(TextureData::textureDataWithColor(usvec2(maxSize, maxSize),
	ucvec4(0, 0, 0, 0)))
{
	tree = new AtlasNode(usrect(usvec2(maxSize, maxSize)));
}

Texture * TextureAtlas::add(TextureData * data)
{
	auto inserted = tree->insert(data);

	if (inserted == nullptr)
	{
		throw runtime_error("Texture Atlas has no more free space\n");
		return nullptr;
	}

	data->addGap(8);
	tex.pixelsReplace(data, inserted->r.p1);

	//Initialize coordinates for Sprite
	auto ret  = new Texture();
	ret->size = data->resolution;
	//Set proper uv coordinates
	const auto gap = data->gap;
	ret->coords[0] = vec2(
		float(inserted->r.p1.x + gap) / float(tree->r.p2.x - gap),
		float(inserted->r.p1.y + data->resolution.y - gap) / float(tree->r.p2.y - gap));
	ret->coords[1] = vec2(
		float(inserted->r.p1.x + gap) / float(tree->r.p2.x - gap),
		float(inserted->r.p1.y + gap) / float(tree->r.p2.y - gap));
	ret->coords[2] = vec2(
		float(inserted->r.p1.x + data->resolution.x - gap) / float(tree->r.p2.x - gap),
		float(inserted->r.p1.y + data->resolution.y - gap) / float(tree->r.p2.y - gap));
	ret->coords[3] = vec2(
		float(inserted->r.p1.x + data->resolution.x - gap) / float(tree->r.p2.x - gap),
		float(inserted->r.p1.y + gap) / float(tree->r.p2.y - gap));

	//Cut rectangle so the other rects can fit there
	if (inserted->cutx)
		inserted->r.p1.x += data->resolution.x;
	else
		inserted->r.p1.y += data->resolution.y;

	return ret;
}

void TextureAtlas::bind()
{
	tex.bind();
}

AtlasNode * AtlasNode::insert(TextureData * tex)
{
	if (!leaf)
	{
		//Try to insert into first child
		AtlasNode * ret = child[0]->insert(tex);
		//If it fails, do the same with the second
		if (ret == nullptr)
			return child[1]->insert(tex);

		return ret;
	}
	else
	{
		if (closed)
			return NULL;

		usvec2 size = r.getSize();

		if (size.x < tex->resolution.x || 
			size.y < tex->resolution.y)
			return NULL;

		auto diff = size - tex->resolution;

		//If it fits perfectly
		if (size.x - tex->resolution.x < MAX_POSSIBLE_GAP || 
			size.y - tex->resolution.y < MAX_POSSIBLE_GAP)
		{
			if (diff.x > diff.y)
				cutx = true;
			return this;
		}

		if (diff.x > diff.y)
		{
			child[0] = new AtlasNode(
				usrect(r.p1, usvec2(r.p1.x + tex->resolution.x, r.p2.y)));
			child[1] = new AtlasNode(
				usrect(usvec2(r.p1.x + tex->resolution.x, r.p1.y), r.p2));
		}
		else
		{
			child[0] = new AtlasNode(
				usrect(r.p1, usvec2(r.p2.x, r.p1.y + tex->resolution.y)));
			child[1] = new AtlasNode(
				usrect(usvec2(r.p1.x, r.p1.y + tex->resolution.y ), r.p2));
		}

		leaf = false;

		return child[0]->insert(tex);
	}
}


TextureAtlas::~TextureAtlas()
{
	tex.release();
	//delete data;
}

}