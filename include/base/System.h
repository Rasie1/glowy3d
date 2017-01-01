/****************************************************************************
This file is part of glowy3d.

Copyright (c) 2015 Kvachev 'Rasie1' V. D.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#pragma once
#include "Platforms/Input.h"

namespace glowy3d
{

class Layer;
class ShaderProgram;
class VertexPosBuffer;
class IndexBuffer;
class Window;
class Renderer;
class Scheduler;
class Config;
class Camera;
class ShaderProgram;
class FramerateCounter;
class Input;

class System
{
public:
	static double getDeltaTime();
	static double getTime();

	static bool init();

	//Global componenets

	static Config			 * config;
	static Window			 * window;
	static Renderer			 * renderer;
	static Camera			 * camera;
	static Scheduler		 * scheduler;
	static FramerateCounter  * framerateCounter;
	static IndexBuffer		 * indexBuffer;
	static unsigned short	   layersNum;

	static bool windowShouldClose();
	static void frameStart();
	static void frameEnded();
	static void exit();
	static bool shouldContinue();
	static void setKeyFunction(Input::Keyboard key,
							   Input::PressType type, 
							   std::function<void()> callback);
private:
	System() {}
	~System() {}
	static double currentTime, lastTime, deltaTime;
};

}
