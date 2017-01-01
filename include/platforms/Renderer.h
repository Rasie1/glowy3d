#pragma once
#include "g2dMath.h"

namespace glowy3d
{

class ShaderProgram;
class UniformMat2;

class Renderer
{
public:
	Renderer();
	~Renderer();

	static double getTime();
	void frameStart();
	void setMatrix(const mat2& modelMatrix, const mat2& cameraMatrix);
	void draw(uint size);
	void pollEvents();
	void render();

	void present(bool vSync);
	void clear();
	void swapBuffers();

	ShaderProgram* shaderProgram;

private:
	UniformMat2* modelMatrixUniform;
	UniformMat2* viewMatrixUniform;
};

}
