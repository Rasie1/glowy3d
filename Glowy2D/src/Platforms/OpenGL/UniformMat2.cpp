#include "epc.h"
#ifdef R_OGL
#include <cassert>
#include "Platforms/UniformMat2.h"
#include "Platforms/Renderer.h"
#include "Platforms/ShaderProgram.h"

namespace glowy2d
{

UniformMat2::UniformMat2(ShaderProgram * program, const string& name, uint location) :
	location(glGetUniformLocation(program->id, name.c_str()))
{
}

UniformMat2::UniformMat2(ShaderProgram * program, const string& name, uint location, const mat2& data) :
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
#endif