#include "epc.h"
#ifdef R_D3D
#include "Platforms/Input.h"
#include "Base/System.h"
#include "Graphics/Camera.h"
#include "Platforms/Window.h"

extern HINSTANCE g_hInstance;

using namespace std;

namespace glowy2d
{

void Input::init()
{
	HRESULT hr;
	hr = DirectInput8Create(
		g_hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&DirectInput,
		NULL);
	if (FAILED(hr))
		throw exception("Failed to init DirectInput8");

	hr = DirectInput->CreateDevice(GUID_SysKeyboard,
		&DIKeyboard,
		NULL);
	if (FAILED(hr))
		throw exception("Failed to init keyboard device");

	hr = DirectInput->CreateDevice(GUID_SysMouse,
		&DIMouse,
		NULL);
	if (FAILED(hr))
		throw exception("Failed to init mouse device");

	hr = DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = DIKeyboard->SetCooperativeLevel(System::window->getHandle(), 
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	hr = DIMouse->SetDataFormat(&c_dfDIMouse);
	hr = DIMouse->SetCooperativeLevel(System::window->getHandle(),
		DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
}

void Input::deinit()
{
	DIKeyboard->Unacquire();
	DIMouse->Unacquire();
	DirectInput->Release();
}

void Input::setUpDefaultControls()
{
	System::camera->setUpDefaultMovementControls();
	setKeyCallback(Keyboard::escape, PressType::press,
		[]()
	{
		PostMessage(System::window->getHandle(), WM_DESTROY, 0, 0); 
	});
}

void Input::process()
{
	Input::DIKeyboard->Acquire();
	//Input::DIMouse->Acquire();
	//Input::DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);
	Input::DIKeyboard->GetDeviceState(sizeof(Input::keyboardState), (LPVOID)&Input::keyboardState);
	
	for (auto i = 0; i < last; ++i)
	{
		if (getKey(static_cast<Input::Keyboard>(i)))
		{
			if (callbacks[PressType::hold][i] != 0)
				callbacks[PressType::hold][i]();
		}
	}

	for (auto i = 0; i < last; ++i)
	{
		if (Input::keyboardState[i] & 0x80)
		{
			if (callbacks[PressType::press][i] != 0)
				callbacks[PressType::press][i]();
		}
	}
}

bool Input::getKey(Input::Keyboard key)
{
	return Input::keyboardState[key] & 0x80;
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

IDirectInputDevice8 * Input::DIKeyboard = nullptr;
IDirectInputDevice8 * Input::DIMouse = nullptr;
BYTE Input::keyboardState[256];
DIMOUSESTATE Input::mouseLastState;
DIMOUSESTATE Input::mouseCurrState;
LPDIRECTINPUT8 Input::DirectInput;

}
#endif