#include "epc.h"
#ifdef R_D3D
#include <cassert>
#include "Platforms/VertexInterleavedBuffer.h"
#include "Platforms/Renderer.h"
#include "Math/vertex.h"

using namespace DirectX;
using namespace std;

using namespace std;
using namespace glm;

namespace glowy3d
{

VertexInterleavedBuffer::VertexInterleavedBuffer(const void * data, uint size)
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.ByteWidth = size;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory(&resourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	
	resourceData.pSysMem = data;

	HRESULT hr = Renderer::d3dDevice->CreateBuffer(&vertexBufferDesc, 
												   &resourceData, 
												   &buffer);
	if (FAILED(hr))
		throw runtime_error("Couldn't init buffer");
}

VertexInterleavedBuffer::~VertexInterleavedBuffer()
{
	deleteBuffer();
}

void VertexInterleavedBuffer::deleteBuffer()
{
	safeRelease(buffer);
}


void VertexInterleavedBuffer::bind()
{
	const UINT vertexStride = sizeof(vertex);
	const UINT offset = 0;

	Renderer::d3dDeviceContext->IASetVertexBuffers(0, 
												   1, 
												   &buffer, 
												   &vertexStride, 
												   &offset);
}

void VertexInterleavedBuffer::setLayoutForPosition()
{
}

void VertexInterleavedBuffer::setLayoutForTextureCoords()
{
}

void VertexInterleavedBuffer::updateData(const void * data, uint size, uint offset)
{
	Renderer::d3dDeviceContext->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
}

void VertexInterleavedBuffer::setLayout()
{
	Renderer::d3dDeviceContext->IASetInputLayout(Renderer::d3dInputLayout);
}

}
#endif
