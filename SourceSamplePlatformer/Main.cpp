
#include "Engine.h"
#include <iostream>
#include "glm/glm.hpp"
#include "Platforms/Input.h"
#include "Graphics/LineLayer.h"
#include "Base/System.h"
#include "Math/AdditionGLM.h"
#include "Math/rect.h"
#include "MapInfo.h"
#include "World.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

using glowy2d::Layer;
using glowy2d::LineLayer;
using glowy2d::Sprite;
using glowy2d::Input;
using namespace game;

World * world;

int init()
{
	world = new World(MapInfo("level1"));

	return 0;
}

void update()
{
	world->update(glowy2d::System::getDeltaTime());
}


#ifdef R_D3D
#include <Windows.h>
#include <io.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)
{
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(cmdLine);
	return glowy2d::glowy2Dmain(init, update, hInstance, cmdShow);
}

#endif

#ifdef R_OGL
int main()
{
	return glowy2d::glowy2Dmain(init, update);
}
#endif

