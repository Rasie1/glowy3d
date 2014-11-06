#include "epc.h"
#include "Platforms/Input.h"
#include "Base/EngineDirector.h"

namespace glowy2d
{
	Input::Input()
	{

	}

	Input::~Input()
	{

	}

	bool Input::getKey(Input::Keyboard key)
	{
		return bool(glfwGetKey(EngineDirector::getInstance()->getWindow(), key));
	}

	void Input::setKeyCallback(Input::Keyboard key, std::function<void(void)> callback)
	{
		callbacks[key] = callback;
	}

	void callbackFunction(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		if (Input::callbacks[key] != 0)
			Input::callbacks[key]();
	}

	std::function<void(void)> Input::callbacks[350];
}