/****************************************************************************
This file is part of glowy2d.

Copyright (c) 2014 Kvachev 'Rasie1' V. D.

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
#include "Base/IncludesEngine.h"
#include "Graphics/Camera.h"
#include "Base/Scheduler.h"
#include "Graphics/FramerateCounter.h"

typedef GLFWwindow WindowHandle;
#define MAX_LAYERS 4096

namespace glowy2d
{
	class Layer;
	class ShaderProgram;
	class VertexBuffer;

	class DLLEXPORT EngineDirector
	{
	public:
		static EngineDirector * getInstance();

		void add(Layer * newLayer);
		
		bool getKey(); 

		//Sets GL program ID
		ShaderProgram * getProgram() const;
		void setProgram(ShaderProgram * program);

		//Sets GL window
		GLFWwindow * getWindow() const;
		void setWindow(WindowHandle * window);

		//Data accessors
		usvec2 getWindowSize() const;
		double getDeltaTime() const;
		
		Camera * camera;
		Scheduler * scheduler;
		FramerateCounter * framerateCounter;

		bool init(WindowHandle * window, ShaderProgram * program);

		void render() const;

		VertexBuffer * indexBuffer;
		ShaderProgram * program;

		int initialization();
		void update();
		void draw(const uint size) const;

		//Layers list
		Layer * layers[MAX_LAYERS];
		unsigned short layersNum;

		bool windowShouldClose();
		static double getTime();
		void frameStart();
		void frameEnded();
		void exit();
		void setKeyCallback(void(*cbfun)(GLFWwindow* w, int a, int b, int c, int d));
		void initEngine();
		bool shouldContinue();

	private:
		EngineDirector();
		~EngineDirector();
		static bool singletonInitialised;
		static EngineDirector singletonInstance;


		//OpenGL data
		WindowHandle * windowHandle;

		//Data
		usvec2 windowSize;

		//Timing
		double currentTime, lastTime, deltaTime;
	};
}