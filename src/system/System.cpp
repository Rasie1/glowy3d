#include "base/System.h"
#include "base/Config.h"
#include "base/Scheduler.h"
#include "graphics/Camera.h"
#include "graphics/Sprite.h"
#include "graphics/Layer.h"
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
using namespace glm;

namespace glowy3d
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
