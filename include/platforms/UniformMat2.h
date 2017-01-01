#pragma once
#include <string>
#include "g2dMath.h"

namespace glowy3d
{

class ShaderProgram;
class UniformMat2
{
public:
	UniformMat2(ShaderProgram* program, 
                const std::string& name, 
                uint location);
	UniformMat2(ShaderProgram* program, 
                const std::string& name, 
                uint location, 
                const mat2& data);
	~UniformMat2();

	void bind();

	void updateData(const mat2& data);

private:
	uint location;
};

}
