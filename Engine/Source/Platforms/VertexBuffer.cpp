#include "epc.h"
#include <cassert>
#include "VertexBuffer.h"

namespace glowy2d
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &id);
	}

	VertexBuffer::~VertexBuffer()
	{
		deleteBuffer();
	}

	void VertexBuffer::deleteBuffer()
	{
		//glDeleteBuffers(size, &id);
	}

	void VertexBuffer::bindForArray() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void VertexBuffer::bindForVertexAttrib() const
	{
		bindForArray();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	void VertexBuffer::bindForTextureAttrib() const
	{
		bindForArray();
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	void VertexBuffer::bindForIndices() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void VertexBuffer::buffer(const uint size, const void * data)
	{
		this->size = size;
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}


	void VertexBuffer::bufferElementArray(const uint size, const void * data)
	{
		this->size = size;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::update(const uint offset, const uint size, const void * data)
	{
		//assert(size + offset <= this->size);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}

}