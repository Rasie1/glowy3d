#include "epc.h"
#ifdef R_OGL
#include <cassert>
#include "Platforms/IndexBuffer.h"
#include "Platforms/Renderer.h"

using namespace std;
using namespace glm;

namespace glowy3d
{

IndexBuffer::IndexBuffer(const void * data, uint size)
{
	bind();
	this->size = size;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}

void IndexBuffer::updateData(const void * data, uint size, uint offset)
{
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}

void IndexBuffer::setLayout()
{
}
	
}
#endif
