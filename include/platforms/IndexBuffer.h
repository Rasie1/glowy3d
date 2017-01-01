#pragma once

namespace glowy3d
{

class IndexBuffer
{
public:
	IndexBuffer(const void *data, unsigned size);
	~IndexBuffer();

	void bind();
	void setLayout();
	void updateData(const void *data, 
                    unsigned size, 
                    unsigned offset);

private:
	unsigned size = 0;
	unsigned bufferId;
};

}
