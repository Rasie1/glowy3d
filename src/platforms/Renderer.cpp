#include "platforms/Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "platforms/ShaderProgram.h"
#include "platforms/Window.h"
#include "base/System.h"
#include "base/Config.h"
#include "platforms/VertexInterleavedBuffer.h"
#include "platforms/IndexBuffer.h"
#include "platforms/UniformMat2.h"
#include <fstream>
#include <chrono>
#include <iostream>


using namespace std;

namespace glowy3d
{

Renderer::Renderer()
{
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("Failed to initialize GLEW");

	cout << "GLEW initialized" << endl;

	// Cull back sides (it works faster with those three on)
	glEnable(GL_CULL_FACE);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSwapInterval(System::config->getMaxFramerate());

}

Renderer::~Renderer()
{
	glfwTerminate();
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::present(bool vSync)
{
}

void Renderer::render()
{
	swapBuffers();
	pollEvents();
	present(System::config->getVSync());
}

void Renderer::setMatrix(const mat2& modelMatrix, 
                         const mat2& cameraMatrix)
{
	viewMatrixUniform->updateData(cameraMatrix);
	modelMatrixUniform->updateData(modelMatrix);
}

void Renderer::frameStart()
{
	clear();
}

void Renderer::draw(uint size)
{
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
}


void Renderer::pollEvents()
{
	glfwPollEvents();
}

chrono::high_resolution_clock::time_point appStartTime = 
	chrono::high_resolution_clock::now();

double Renderer::getTime()
{
	return glfwGetTime();
}

void Renderer::swapBuffers()
{
	glfwSwapBuffers(System::window->getHandle());
}

}
