#include "epc.h"
#ifdef R_OGL
#include "Platforms/Renderer.h"
#include "Platforms/ShaderProgram.h"
#include "Platforms/Window.h"
#include "Base/System.h"
#include "Base/Config.h"
#include "Platforms/VertexInterleavedBuffer.h"
#include "Platforms/IndexBuffer.h"
#include "Platforms/UniformMat2.h"
#include <fstream>
#include <chrono>


using namespace std;

namespace glowy3d
{

Renderer::Renderer()
{
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("Failed to initialize GLEW");

	cout << "GLEW OK" << endl;

	// Cull back sides (it works faster with those three on)
	glEnable(GL_CULL_FACE);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSwapInterval(System::config->getMaxFramerate());

	shaderProgram = new ShaderProgram("Shaders\\Texture.vsh", "Shaders\\Texture.fsh");
	shaderProgram->use();

	modelMatrixUniform = new UniformMat2(shaderProgram, "model", 0);
	modelMatrixUniform->bind();
	viewMatrixUniform = new UniformMat2(shaderProgram, "camera", 1);
	viewMatrixUniform->bind();
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

void Renderer::setMatrix(const mat2& modelMatrix, const mat2& cameraMatrix)
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
#endif
