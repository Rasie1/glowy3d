#include "epc.h"
#ifdef R_OGL
#include "Base/System.h"
#include "Graphics/Camera.h"
#include "Platforms/Window.h"
#include "Platforms/Input.h"

using namespace std;
using namespace glm;

namespace glowy3d
{

void callbackFunction(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (Input::callbacks[action][key] != 0)
		Input::callbacks[action][key]();
	Input::isKeyPressed[key] = (bool)action;
}

void Input::init()
{
	glfwSetKeyCallback(System::window->getHandle(),
		callbackFunction);
}

void Input::deinit()
{
}

void Input::setUpDefaultControls()
{
	System::camera->setUpDefaultMovementControls();
	setKeyCallback(Keyboard::escape, PressType::press, 
		[](){glfwSetWindowShouldClose(System::window->getHandle(), 1); });
}

void Input::process()
{
	for (uint16 i = 32; i < 350; ++i)
	{
		if (isKeyPressed[i])
		{
			if (callbacks[PressType::hold][i] != 0)
				callbacks[PressType::hold][i]();
		}
	}
}

bool Input::getKey(Input::Keyboard key)
{
	return Input::isKeyPressed[key];
}

void Input::setKeyCallback(Input::Keyboard key, Input::PressType type, std::function<void(void)> callback)
{
	callbacks[type][key] = callback;
}

void Input::resetKeyCallback(Keyboard key, PressType type)
{
	callbacks[type][key] = nullptr;
}

std::function<void(void)> Input::callbacks[3][350];
bool Input::isKeyPressed[350] = { 0 };

}
#endif
