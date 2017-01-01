#include "epc.h"
#ifdef R_D3D
#include <cassert>
#include "Platforms/IndexBuffer.h"
#include "Platforms/Renderer.h"

using namespace DirectX;
using namespace std;

using namespace std;
using namespace glm;

namespace glowy3d
{

IndexBuffer::IndexBuffer(const void * data, uint size)
{
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = size;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA resourceData;

	resourceData.pSysMem = data;
	HRESULT hr = 
		glowy3d::Renderer::d3dDevice->CreateBuffer(&indexBufferDesc, 
												   &resourceData, 
												   &bufferId);
	if (FAILED(hr))
		throw exception("Couldn't initialize Index Buffer");
}

IndexBuffer::~IndexBuffer()
{
	safeRelease(bufferId);
}

void IndexBuffer::bind()
{
	glowy3d::Renderer::d3dDeviceContext->IASetIndexBuffer(bufferId, DXGI_FORMAT_R32_UINT, 0);
}

void IndexBuffer::updateData(const void * data, uint size, uint offset)
{
}

void IndexBuffer::setLayout()
{
}
	
}
#endif
