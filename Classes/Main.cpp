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
#include "EngineDirector.h"
using glowy2d::Layer;
using glowy2d::Sprite;
using glowy2d::EngineDirector;

/****************************************************************************
Test or use glowy2d through this file
****************************************************************************/

const int snum = sqrt(10922);
const int lnum = sqrt(10922);
auto l = new Layer*[lnum];
auto x = new Sprite**[lnum];
Sprite * s;


int EngineDirector::initialization()
{

	l[0] = Layer::create(snum * lnum);
	auto t = new TextureInfo*[2];
	t[0] = l[0]->addTexture("Internet.bmp");
	t[1] = l[0]->addTexture("test.bmp");

	for (int i = 0; i < lnum; ++i)
	for (int j = 0; j < snum; ++j)
	{
		s = l[0]->add(t[rand() % 2]);
		s->setPosition(vec2(j, i) * 256.f);
	}
	l[0]->initBuffers();
	/*
	TextureInfo *** t = new TextureInfo**[lnum];

	for (int j = 0; j < lnum; ++j)
	{
		l[j] = Layer::create(snum);
		t[j] = new TextureInfo*[3];
		//t[j][0] = l[j]->addTexture("grass.bmp");
		t[j][1] = l[j]->addTexture("Internet.bmp");
		t[j][2] = l[j]->addTexture("test.bmp");
		x[j] = new Sprite*[snum];
		for (int i = 0; i < snum; ++i)
		{
			x[j][i] = l[j]->add(t[j][rand() % 2 + 1]);
			x[j][i]->setPosition(vec2(j, i) * 256.f);
		}
		
		l[j]->initBuffers();
	}*/

	return 0;
}

void EngineDirector::update()
{
	l[0]->draw();
	for (int j = 0; j < lnum; ++j)
	{
		/*if (1)
		{
			for (int i = 0; i < snum; ++i)
			{
				//x[j][i]->addPosition(vec2(double(rand()) / double(RAND_MAX) - 0.5f, double(rand()) / double(RAND_MAX) - 0.5f) / 1.f);
				x[j][i]->addPosition(vec2(0.10f, 0.f));
				//x[j][i]->setZOrder(double(rand()) / double(RAND_MAX));

			}
		}
		l[j]->updateVertexBuffer();*/
		//l[j]->draw();
	}
}