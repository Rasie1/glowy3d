#pragma once
#include <string> 

namespace glowy3d
{

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertexPath, 
                  const std::string& fragmentPath);
	~ShaderProgram();

	void use();
	void setInputLayout();

	unsigned id;
private:
	void reportErrors();
};

}
