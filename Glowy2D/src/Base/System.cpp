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
#include "Base/System.h"
#include "Base/Config.h"
#include "Base/Scheduler.h"
#include "Graphics/Camera.h"
#include "Graphics/Sprite.h"
#include "Graphics/Layer.h"
#include "Graphics/FramerateCounter.h"
#include "Platforms/Renderer.h"
#include "Platforms/ShaderProgram.h"
#include "Platforms/UniformMat2.h"
#include "Platforms/IndexBuffer.h"
#include "Platforms/Input.h"
#include "Platforms/Window.h"
#include "Platforms/VertexInterleavedBuffer.h"
#include "Graphics/TextureData.h"
#include "Platforms/Tex2D.h"
#include "png.h"


namespace glowy2d
{

#ifdef R_D3D
using namespace DirectX;
HRESULT hr;
#endif

Config			 * System::config;
Window			 * System::window;
Renderer		 * System::renderer;
Camera			 * System::camera;
Scheduler		 * System::scheduler;
FramerateCounter * System::framerateCounter;
IndexBuffer		 * System::indexBuffer;
unsigned short	   System::layersNum;
double			   System::currentTime;
double			   System::lastTime;
double			   System::deltaTime;

bool System::init()
{
	cout << "-- Reading config.txt" << endl;
	config   = new Config("config.txt");
	cout << "-- Initializing window" << endl;
	window = new Window();
	cout << "-- Done" << endl;
	camera = new Camera();
	cout << "-- Initializing renderer" << endl;
	renderer = new Renderer();
	cout << "-- Done; Starting application" << endl;
	scheduler = new Scheduler();
	Input::init();
	framerateCounter = new FramerateCounter();
	scheduler->add(framerateCounter, 1.0);

	deltaTime = 0;
	layersNum = 0;

	const uint maxSpritesPerLayer = 800 * 800;
	const uint iboSize			  = maxSpritesPerLayer * 6;
	uint     * iboList = new uint[iboSize];

	for (int iVertex = 0, i = 0; i < iboSize; iVertex += 4, i += 6)
	{
		iboList[i]	   = iVertex;
		iboList[i + 1] = iVertex + 1;
		iboList[i + 2] = iVertex + 2;
		iboList[i + 3] = iVertex + 3;
		iboList[i + 4] = iVertex + 2;
		iboList[i + 5] = iVertex + 1;
	}

	indexBuffer = new IndexBuffer(iboList, iboSize * sizeof(uint));
	indexBuffer->bind();

	delete[] iboList;

	Input::setUpDefaultControls();

	return true;
}

double System::getDeltaTime()
{
	return deltaTime;
}

bool System::windowShouldClose()
{
	return bool(window->shouldClose());
}

double System::getTime()
{
	return Renderer::getTime();
}

void System::frameStart()
{
	Input::process();
	renderer->setMatrix(mat2(1.f, 0.f, 0.f, 1.f), camera->getMatrix());
	renderer->frameStart();

	//Timing stuff
	deltaTime	= currentTime - lastTime;
	lastTime	= currentTime;
	currentTime = getTime();
	//Scheduler
	scheduler->check(currentTime);
	framerateCounter->countFrameStart(currentTime);
}


void System::frameEnded()
{
	framerateCounter->countFrameEnd(getTime());
	renderer->render();
}

void System::exit()
{
	Input::deinit();
	delete indexBuffer;
	delete framerateCounter;
	delete scheduler;
	delete camera;
	delete renderer;
	delete window;
	std::exit(EXIT_SUCCESS);
}

bool System::shouldContinue()
{
	return !windowShouldClose();
}

}