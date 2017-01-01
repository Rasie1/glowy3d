#pragma once

namespace glowy3d
{

class VertexInterleavedBuffer
{
public:
	VertexInterleavedBuffer(const void *data, unsigned size);
	~VertexInterleavedBuffer();

	void bind();
	void setLayout();
	void setLayoutForPosition();
	void setLayoutForTextureCoords();
	void updateData(const void *data, 
                    unsigned size, 
                    unsigned offset);

	//static void setLayout();
	friend class ShaderProgram;
private:
	void deleteBuffer();

	unsigned size = 0;
	unsigned id;
};
	
}
