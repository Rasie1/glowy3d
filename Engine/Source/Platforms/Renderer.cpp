#include "epc.h"
#include "Platforms\ShaderProgram.h"


namespace glowy2d
{
	namespace Renderer
	{
		void mvp(const glm::mat4& MVP, ShaderProgram * program)
		{
			GLuint MatrixID = glGetUniformLocation(program->id, "mvp");
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		}

		void frameStart()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}
}