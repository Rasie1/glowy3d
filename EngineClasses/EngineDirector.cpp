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

#define MAX_LAYERS 4096

namespace glowy2d
{
	bool EngineDirector::singletonInitialised;
	EngineDirector EngineDirector::singletonInstance;

	bool EngineDirector::init(GLFWwindow * window, unsigned program_id)
	{
		setWindow(window);
		setProgram(program_id);

		camera = new Camera();
		deltaTime = 0;

		layers = new Layer*[MAX_LAYERS];
		layersNum = 0;

		windowSize = usvec2(SCREEN_WEED, SCREEN_HATE);
		glGenBuffers(1, &ibo_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Constants::triangleList), Constants::triangleList, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		

		return true;
	}

	void EngineDirector::add(Layer * newLayer)
	{
		layers[layersNum++] = newLayer;
	}

	EngineDirector::EngineDirector()
	{
		singletonInitialised = true;
	}

	EngineDirector::~EngineDirector()
	{
		singletonInitialised = false;
	}

	void EngineDirector::render() const
	{
		for (int i = 0; i < layersNum; ++i)
			layers[i]->draw();
	}

	EngineDirector * EngineDirector::getInstance()
	{
		return singletonInitialised ? &singletonInstance : 0;
	}

	void EngineDirector::setProgram(unsigned programId)
	{
		program_id = programId;
		glUseProgram(program_id);
	}

	unsigned EngineDirector::getProgram() const
	{
		return program_id;
	}

	GLFWwindow * EngineDirector::getWindow() const
	{
		return windowHandle;
	}

	void EngineDirector::setWindow(GLFWwindow * window)
	{
		windowHandle = window;
	}

	usvec2 EngineDirector::getWindowSize() const
	{
		return windowSize;
	}

	double EngineDirector::getDeltaTime() const
	{
		return deltaTime;
	}

	void EngineDirector::update_16ms()
	{

	}
}