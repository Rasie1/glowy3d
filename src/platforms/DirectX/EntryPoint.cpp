#include "epc.h"
#ifdef R_D3D
#include "Engine.h"
#include "Base/System.h"

extern HINSTANCE g_hInstance;
extern int g_cmdShow;
extern MSG g_msg;

using namespace std;
using namespace glm;

namespace glowy3d
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
		if (PeekMessage(&g_msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&g_msg);
			DispatchMessage(&g_msg);
			continue;
		}

		System::frameStart();
		update();
		System::frameEnded();
	}

	System::exit();
	return 0;
}

int glowy2Dmain(int(*init)(), void(*update)(),
	HINSTANCE__ * hInstance, int cmdShow)
{
	g_hInstance = hInstance;
	g_cmdShow = cmdShow;

	return glowy2Dmain(init, update);
}
	
}
#endif
