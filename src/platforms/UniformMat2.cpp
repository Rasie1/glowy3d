#include "platforms/UniformMat2.h"
#include <cassert>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "platforms/Renderer.h"
#include "platforms/ShaderProgram.h"

using namespace std;

namespace glowy3d
{

UniformMat2::UniformMat2(ShaderProgram* program, 
                         const string& name, 
                         uint location) :
	location(glGetUniformLocation(program->id, name.c_str()))
{
}

UniformMat2::UniformMat2(ShaderProgram* program, 
                         const string& name, 
                         uint location, 
                         const mat2& data) :
	UniformMat2(program, name, location)
{
	updateData(data);
}

UniformMat2::~UniformMat2()
{
}

void UniformMat2::updateData(const mat2& data)
{
	glUniformMatrix2fv(location, 1, GL_FALSE, &data[0][0]);
}

void UniformMat2::bind()
{
}
	
}
