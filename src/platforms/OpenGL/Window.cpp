#include "epc.h"
#ifdef R_OGL
#include "Platforms/Window.h"
#include "Platforms/Renderer.h"
#include "Base/System.h"
#include "Base/Config.h"

using namespace std;

namespace glowy2d
{

static void error_callback(int error, const char * description)
{
	fputs(description, stderr);
	throw runtime_error("GLFW error");
}

Window::Window() :
	size(System::config->getScreenResolution())
{
	if (!glfwInit())
		throw std::runtime_error("Failed to initialize GLFW");

	glfwSetErrorCallback(error_callback);

	//Window hints
	glfwWindowHint(GLFW_SAMPLES, System::config->getAntialiasing()); //Anti-aliasing

	/* Unused window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //For Mac OS
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //To turn off old versions
	glewExperimental = true;
	*/
	handle = glfwCreateWindow(size.x, size.y, "My Game", NULL, NULL);

	if (!handle)
	{
		fprintf(stderr, "Failed to initialize a GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(handle);
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
	return glfwWindowShouldClose(handle);
}

void Window::close()
{
	glfwSetWindowShouldClose(handle, GL_TRUE);
}

void Window::setText(const char * str)
{
	glfwSetWindowTitle(handle, str);
}

usvec2 Window::getSize() const
{
	return size;
}

}
#endif