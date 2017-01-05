#include "base/System.h"
#include <iostream>
#include "base/Config.h"
#include "base/Scheduler.h"
#include "graphics/Camera.h"
#include "graphics/FramerateCounter.h"
#include "platforms/Renderer.h"
#include "platforms/ShaderProgram.h"
#include "platforms/UniformMat2.h"
#include "platforms/IndexBuffer.h"
#include "platforms/Input.h"
#include "platforms/Window.h"
#include "platforms/VertexInterleavedBuffer.h"
#include "graphics/TextureData.h"
#include "platforms/Tex2D.h"
#include "png.h"

using namespace std;

namespace glowy3d
{

Config			 * System::config;
Window			 * System::window;
Renderer		 * System::renderer;
Camera			 * System::camera;
Scheduler		 * System::scheduler;
FramerateCounter * System::framerateCounter;
unsigned short	   System::layersNum;
double			   System::currentTime;
double			   System::lastTime;
double			   System::deltaTime;

bool System::init()
{
	cout << "Reading config.txt" << endl;
	config   = new Config("config.txt");
	cout << "Initializing window" << endl;
	window = new Window();
	cout << "Done initializing window" << endl;
	camera = new Camera();
	cout << "Initializing renderer" << endl;
	renderer = new Renderer();
	cout << "Done initializing renderer" << endl;
    cout << "Starting application" << endl;
	scheduler = new Scheduler();
	Input::init();
	framerateCounter = new FramerateCounter();
	scheduler->add(framerateCounter, 1.0);

	deltaTime = 0;

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
	delete framerateCounter;
	delete scheduler;
	delete renderer;
	delete window;
	std::exit(EXIT_SUCCESS);
}

bool System::shouldContinue()
{
	return !windowShouldClose();
}

}
