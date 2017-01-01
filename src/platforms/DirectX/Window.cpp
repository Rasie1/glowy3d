#include "epc.h"
#ifdef R_D3D
#include "Platforms/Window.h"
#include "Platforms/Renderer.h"
#include "Base/System.h"
#include "Base/Config.h"

#include <DirectXMath.h>
#include <DirectXMathMatrix.inl>

HINSTANCE g_hInstance = 0;
int g_cmdShow = 0;
MSG g_msg = { 0 };

#define IDI_ICON1                       103

#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        105
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintStruct;
	HDC hDC;

	switch (message)
	{
		case WM_PAINT:
		{
							hDC = BeginPaint(hwnd, &paintStruct);
							EndPaint(hwnd, &paintStruct);
							break;
		}
		case WM_DESTROY:
		{
							PostQuitMessage(0);
							break;
		}
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

using namespace std;
using namespace std;
using namespace glm;

namespace glowy3d
{

static void error_callback(int error, const char * description)
{
	fputs(description, stderr);
	throw runtime_error("GLFW error");
}

Window::Window() :
	size(System::config->getScreenResolution())
{
	WNDCLASSEX wndClass    = { 0 };
	wndClass.cbSize 	   = sizeof(WNDCLASSEX);
	wndClass.style 		   = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc   = &WndProc;
	wndClass.hInstance 	   = g_hInstance;
	wndClass.hCursor 	   = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hIcon 		   = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName  = nullptr;
	wndClass.lpszClassName = windowClassName;

	if (!RegisterClassEx(&wndClass))
		throw runtime_error("Couldn't create the window");

	RECT windowRect = { 0, 0, 
		System::config->getScreenResolution().x, 
		System::config->getScreenResolution().y };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	handle = CreateWindowA(windowClassName, windowName,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, nullptr, g_hInstance, nullptr);

	if (!handle)
		throw runtime_error("Couldn't create the window");

	ShowWindow(handle, g_cmdShow);
	UpdateWindow(handle);
}

Window::~Window()
{
}

WindowHandle * Window::getHandle() const
{
	return handle;
}

int Window::shouldClose()
{
	return g_msg.message == WM_QUIT;
}

void Window::close()
{
}

void Window::setText(const char * str)
{
	SetWindowText(handle, str);
}

}
#endif
