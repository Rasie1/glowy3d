#include "epc.h"
#ifdef R_OGL
#include <cassert>
#include "Platforms/VertexInterleavedBuffer.h"
#include "Platforms/Renderer.h"
#include "Math/vertex.h"

using namespace std;

namespace glowy2d
{

VertexInterleavedBuffer::VertexInterleavedBuffer(const void * data, uint size)
{
	glGenBuffers(1, &id);

	bind();
	this->size = size;
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

VertexInterleavedBuffer::~VertexInterleavedBuffer()
{
	deleteBuffer();
}

void VertexInterleavedBuffer::deleteBuffer()
{
}


void VertexInterleavedBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexInterleavedBuffer::setLayoutForPosition()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
}

void VertexInterleavedBuffer::setLayoutForTextureCoords()
{
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 
						  2, 
						  GL_FLOAT, 
						  GL_FALSE, 
						  sizeof(vertex), 
						  (void*)offsetof(vertex, vertex::texture));
}

void VertexInterleavedBuffer::updateData(const void * data, uint size, uint offset)
{
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexInterleavedBuffer::setLayout()
{
	setLayoutForTextureCoords();
	setLayoutForPosition();
}

}
#endif