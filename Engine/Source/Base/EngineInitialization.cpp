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
#include "epc.h"
#include "Base/EngineInitialization.h"
//#include "Base/FileOperation.h"
#include <string>
#include <fstream>
#include <vector>


namespace glowy2d
{

	std::string readFile(const char *filePath)
	{
		std::string content;
		std::ifstream fileStream(filePath, std::ios::in);

		if (!fileStream.is_open())
		{
			std::cout << "Could not read file " << filePath << ". File does not exist." << std::endl;
			return "";
		}

		std::string line = "";
		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			content.append(line + "\n");
		}

		fileStream.close();
		return content;
	}




	GLuint EngineInitialization::loadShader(const char *vertex_path, const char *fragment_path)
	{
		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Read shaders
		std::string vertShaderStr = readFile(vertex_path);
		std::string fragShaderStr = readFile(fragment_path);
		const char *vertShaderSrc = vertShaderStr.c_str();
		const char *fragShaderSrc = fragShaderStr.c_str();

		GLint result = GL_FALSE;
		int logLength;

		// Compile vertex shader
		std::cout << "Compiling vertex shader." << std::endl;
		glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
		glCompileShader(vertShader);

		// Check vertex shader
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
		glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
		std::cout << &vertShaderError[0] << std::endl;

		// Compile fragment shader
		std::cout << "Compiling fragment shader." << std::endl;
		glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
		glCompileShader(fragShader);

		// Check fragment shader
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
		glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
		std::cout << &fragShaderError[0] << std::endl;

		std::cout << "Linking program" << std::endl;
		GLuint program = glCreateProgram();
		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);
		glLinkProgram(program);

		glGetProgramiv(program, GL_LINK_STATUS, &result);
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> programError((logLength > 1) ? logLength : 1);
		glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
		std::cout << &programError[0] << std::endl;

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

		return program;
	}


	static void error_callback(int error, const char* description)
	{
		fputs(description, stderr);
	}

	GLFWwindow * EngineInitialization::createWindow()
	{
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize a GLFW\n");
			exit(EXIT_FAILURE);
		}

		GLFWwindow * window;
		glfwSetErrorCallback(error_callback);


		//Window hints
		glfwWindowHint(GLFW_SAMPLES, Constants::antialiasing); //Anti-aliasing


		/* Unused window hints
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //For Mac OS
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //To turn off old versions
		glewExperimental = true;
		*/

		//auto director = EngineDirector::getInstance();
		auto windowSize = usvec2(SCREEN_WEED, SCREEN_HATE);

		window = glfwCreateWindow(windowSize.x, windowSize.y, "My Game", NULL, NULL);
		if (!window)
		{
			fprintf(stderr, "Failed to initialize a GLFW window\n");
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		glfwMakeContextCurrent(window);

		// initialize GLEW
		if (glewInit() != GLEW_OK){
			fprintf(stderr, "Failed to initialize GLEW\n");
		}

		//SETTINGS

		// Cull back sides (it works faster with those three on)
		glEnable(GL_CULL_FACE);
		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Disable V-Sync
		glfwSwapInterval(Constants::maxFPS);


		return window;
	}
}