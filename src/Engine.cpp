#include "Engine.h"
#include <iostream>
#include "base/System.h"

using namespace std;

namespace glowy3d
{

void start(void(*init)(), void(*update)())
{
	std::cout << "-- Starting engine" << std::endl;
	System::init();
	std::cout << "-- System initialization done, starting game" << std::endl;
	init();
	std::cout << "-- Initialization done" << std::endl;

	while (System::shouldContinue())
	{
		System::frameStart();
		update();
		System::frameEnded();
	}

	System::exit();
}

}
