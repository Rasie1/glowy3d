#include "epc.h"
#ifdef R_OGL
#include "Engine.h"
#include "Base/System.h"

namespace glowy2d
{

int glowy2Dmain(int(*init)(), void(*update)())
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
	return 0;
}

}
#endif