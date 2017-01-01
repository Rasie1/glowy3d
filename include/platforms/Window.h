#pragma once
#include "g2dMath.h"

struct GLFWwindow;
typedef GLFWwindow WindowHandle;

namespace glowy3d
{

class Window
{
public:
	Window();
	~Window();

	int    shouldClose();
	void   close();
	usvec2 getSize() const;
	void   setText(const char *str);

	WindowHandle* getHandle() const;

private:
	WindowHandle* handle;
	usvec2 size;
};

}
