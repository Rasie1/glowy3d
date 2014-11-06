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
#include "Base/IncludesEngine.h"
#include "Base/EngineInitialization.h"
#include "Graphics/Camera.h"
#include "Graphics/Sprite.h"
#include "Graphics/Layer.h"
#include "Base/EngineDirector.h"
#include "Platforms/Renderer.h"
#include "Platforms/ShaderProgram.h"
#include "Platforms/VertexBuffer.h"
#include "Platforms/Input.h"
#include "png.h"

using namespace glowy2d;

bool key_hold_w = false;
bool key_hold_a = false;
bool key_hold_s = false;
bool key_hold_d = false;
bool key_hold_space = false;
bool key_hold_shift = false;
EngineDirector * g_director;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
	}
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		key_hold_w = true;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		key_hold_s = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		key_hold_d = true;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		key_hold_a = true;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		key_hold_space = true;
	}
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
	{
		key_hold_shift = true;
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		key_hold_w = false;
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		key_hold_s = false;
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		key_hold_d = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		key_hold_a = false;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		key_hold_space = false;
	}
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
	{
		key_hold_shift = false;
	}
}

void processInput()
{
	
	if (key_hold_w)
	{
		g_director->camera->addPosition(vec2(0.f, -MOVE_SPEED * g_director->getDeltaTime()));
	}
	if (key_hold_s)
	{
		g_director->camera->addPosition(vec2(0.f, MOVE_SPEED * g_director->getDeltaTime()));
	}
	if (key_hold_d)
	{
		g_director->camera->addPosition(vec2(-MOVE_SPEED * g_director->getDeltaTime(), 0.f));
	}
	if (key_hold_a)
	{
		g_director->camera->addPosition(vec2(MOVE_SPEED * g_director->getDeltaTime(), 0.f));
	}
	if (key_hold_space)
	{
		g_director->camera->addZoom(-ZOOM_SPEED * g_director->getDeltaTime());
	}
	if (key_hold_shift)
	{
		g_director->camera->addZoom(ZOOM_SPEED * g_director->getDeltaTime());
	}
}


//Old main end



namespace glowy2d
{
	bool EngineDirector::singletonInitialised;
	EngineDirector EngineDirector::singletonInstance;

	bool EngineDirector::init(GLFWwindow * window, ShaderProgram * program)
	{
		setWindow(window);
		setProgram(program);

		camera = new Camera();
		scheduler = new Scheduler();
		framerateCounter = new FramerateCounter();
		scheduler->add(framerateCounter, 1.0);

		deltaTime = 0;

		layersNum = 0;

		windowSize = usvec2(SCREEN_WEED, SCREEN_HATE);

		const uint maxSpritesPerLayer = 800 * 800;
		const uint iboSize = maxSpritesPerLayer * 6;
		uint * iboList = new uint[iboSize];

		for (int iVertex = 0, i = 0; i < iboSize; iVertex += 4, i += 6)
		{
			iboList[i] = iVertex;
			iboList[i + 1] = iVertex + 1;
			iboList[i + 2] = iVertex + 2;
			iboList[i + 3] = iVertex + 3;
			iboList[i + 4] = iVertex + 2;
			iboList[i + 5] = iVertex + 1;
		}

		indexBuffer = new VertexBuffer();
		indexBuffer->bindForIndices();
		indexBuffer->bufferElementArray(iboSize * 4, iboList);

		delete[] iboList;
		return true;
	}

	void EngineDirector::draw(const uint size) const
	{
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
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

		delete indexBuffer;
		delete framerateCounter;
		delete scheduler;
		delete camera;
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

	void EngineDirector::setProgram(ShaderProgram * program)
	{
		this->program = program;
		program->use();
	}

	ShaderProgram * EngineDirector::getProgram() const
	{
		return program;
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


	bool EngineDirector::windowShouldClose()
	{
		return bool(glfwWindowShouldClose(windowHandle));
	}

	double EngineDirector::getTime()
	{
		return glfwGetTime();
	}

	void EngineDirector::frameStart()
	{
		processInput();
		//GL stuff
		Renderer::mvp(camera->getMatrix(), program);
		Renderer::frameStart();


		//Timing stuff
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		currentTime = getTime();
		//Scheduler
		scheduler->check(currentTime);
		framerateCounter->countFrameStart(currentTime);
	}

	void EngineDirector::frameEnded()
	{
		framerateCounter->countFrameEnd(getTime());
		glfwSwapBuffers(windowHandle);
		glfwPollEvents();
	}

	void EngineDirector::exit()
	{
		glfwDestroyWindow(windowHandle);
		glfwTerminate();
		std::exit(EXIT_SUCCESS);
	}

	void EngineDirector::setKeyCallback(void(*cbfun)(GLFWwindow* w, int a, int b, int c, int d))
	{
		glfwSetKeyCallback(windowHandle, cbfun);
	}

	void EngineDirector::initEngine()
	{
		g_director = EngineDirector::getInstance();
		auto window = EngineInitialization::createWindow();
		g_director->init(window,
			ShaderProgram::load("Shaders\\Texture.vsh", "Shaders\\Texture.fsh"));

		g_director->setKeyCallback(key_callback);

		/*for (uint i = 0; i < 350; ++i)
		{
			Input::callbacks[i] = nullptr;
		}
		g_director->setKeyCallback(callbackFunction);*/
		

		g_director->initialization();

	}

	bool EngineDirector::shouldContinue()
	{
		return !windowShouldClose();
	}


	int EngineDirector::initialization()
	{

		return 0;
	}

	void EngineDirector::update()
	{

	}
}