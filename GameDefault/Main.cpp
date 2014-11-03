#include "glm/glm.hpp"
#include "Engine.h"

using glowy2d::Layer;
using glowy2d::Sprite;
using glowy2d::EngineDirector;


int main()
{
	//Engine init
	auto director = EngineDirector::getInstance();
	director->initEngine();

	//User content
	auto layer = new Layer(256);
	auto s = layer->add("grass_0_0.png");
	layer->initBuffers();


	while (director->shouldContinue())
	{
		//Engine frame start
		director->frameStart();
		director->update();
		//User content update
		layer->updateVertexBuffer();
		layer->draw();
		s->addRotation(1.f);

		director->frameEnded();
	}

	director->exit();
}

