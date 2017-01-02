#include "base/System.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/TextureData.h"
#include "platforms/Tex2D.h"
#include "platforms/Renderer.h"

using namespace std;

namespace glowy3d
{

Tex2D::Tex2D(TextureData* data) :
	size(data->resolution)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	
	glTexImage2D(GL_TEXTURE_2D, 
				 0, 
				 GL_RGBA, 
				 size.x, 
				 size.y, 0, 
				 GL_RGBA, 
				 GL_UNSIGNED_BYTE, 
				 data->data);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	/*glGenerateMipmap(GL_TEXTURE_2D);*/
}

void Tex2D::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

Tex2D::Tex2D(const char *filename) : Tex2D(TextureData::load(filename))
{
}

Tex2D::~Tex2D()
{
}

void Tex2D::release()
{
	glDeleteTextures(1, &id);
}

void Tex2D::pixelsReplace(TextureData* data, usvec2 offset)
{
	bind();
	glTexSubImage2D(GL_TEXTURE_2D, 0, offset.x, offset.y, data->resolution.x, data->resolution.y, GL_RGBA, GL_UNSIGNED_BYTE, data->data);
	//glGenerateMipmap(GL_TEXTURE_2D);
}

}
