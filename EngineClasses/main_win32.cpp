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
#include "stdafx.h"
#include "IncludesEngine.h"
#include "EngineInitialization.h"
#include "Camera.h"
#include "Sprite.h"
#include "Layer.h"
#include "EngineDirector.h"

using namespace glowy2d;

bool key_hold_w = false;
bool key_hold_a = false;
bool key_hold_s = false;
bool key_hold_d = false;
bool key_hold_space = false;
bool key_hold_shift = false;
EngineDirector * g_director;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
	}
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		key_hold_w = true;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		key_hold_s = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		key_hold_d = true;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		key_hold_a = true;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		key_hold_space = true;
	}
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
	{
		key_hold_shift = true;
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		key_hold_w = false;
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		key_hold_s = false;
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		key_hold_d = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		key_hold_a = false;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		key_hold_space = false;
	}
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
	{
		key_hold_shift = false;
	}
}

void processInput()
{
	if (key_hold_w)
	{
		g_director->camera->addPosition(vec2(0.f, -MOVE_SPEED * g_director->getDeltaTime()));
	}
	if (key_hold_s)
	{
		g_director->camera->addPosition(vec2(0.f, MOVE_SPEED * g_director->getDeltaTime()));
	}
	if (key_hold_d)
	{
		g_director->camera->addPosition(vec2(-MOVE_SPEED * g_director->getDeltaTime(), 0.f));
	}
	if (key_hold_a)
	{
		g_director->camera->addPosition(vec2(MOVE_SPEED * g_director->getDeltaTime(), 0.f));
	}
	if (key_hold_space)
	{
		g_director->camera->addZoom(ZOOM_SPEED * g_director->getDeltaTime());
	}
	if (key_hold_shift)
	{
		g_director->camera->addZoom(-ZOOM_SPEED * g_director->getDeltaTime());
	}
}



int main(void)
{
	g_director = EngineDirector::getInstance();
	auto window = EngineInitialization::createWindow();
	g_director->init(window,
		EngineInitialization::loadShader("Shaders\\Texture.vsh", "Shaders\\Texture.fsh"));

	glfwSetKeyCallback(window, key_callback);

	//Timing stuff
	float lastTime = 0.f;
	float lastTimeSecond = 0.f;
	int nbFrames = 0;
	double avgTimeToDraw = 0.0;


	g_director->initialization();

	while (!glfwWindowShouldClose(window))
	{
		processInput();

		//TIMING STUFF
		float currentTime = float(glfwGetTime());
		g_director->deltaTime = currentTime - lastTime;
		//FPS
		nbFrames++;
		if (currentTime - lastTimeSecond >= 1.0f)
		{ // If last prinf() was more than 1 sec ago
			// printf and reset timer
			printf("TTD: %f\nFPS: %d\n", avgTimeToDraw / (double)nbFrames, nbFrames);
			nbFrames = 0;
			avgTimeToDraw = 0.0;
			lastTimeSecond = currentTime;
		}
		lastTime = currentTime;

		//VIEW TRANSFORM STUFF
		const glm::mat4& MVP = g_director->camera->getMatrix();
		GLuint MatrixID = glGetUniformLocation(g_director->getProgram(), "mvp");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		currentTime = glfwGetTime();


		g_director->update();


		avgTimeToDraw += glfwGetTime() - currentTime;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	std::exit(EXIT_SUCCESS);
}