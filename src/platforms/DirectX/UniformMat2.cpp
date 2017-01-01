#include "epc.h"
#ifdef R_D3D
#include <cassert>
#include "Platforms/UniformMat2.h"
#include "Platforms/Renderer.h"
#include "Platforms/ShaderProgram.h"
#include <d3d11shader.h>
#include <d3dcompiler.h>

using namespace DirectX;
using namespace std;

using namespace std;
using namespace glm;

namespace glowy3d
{

UniformMat2::UniformMat2(ShaderProgram * program, const string& name, uint location) :
	location(location)
{
	//Create the buffer to send to the cbuffer in effect file
	HRESULT hr(0);

	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));
	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = 32;
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;// D3D11_CPU_ACCESS_WRITE;
	System::renderer->d3dDevice->CreateBuffer(&cbbd, NULL, &buffer);
	if (FAILED(hr))
		throw runtime_error("Couldn't create constant buffer");
}

UniformMat2::UniformMat2(ShaderProgram * program, const string& name, uint location, const mat2& data) :
	UniformMat2(program, name, location)
{
	updateData(data);
}

UniformMat2::~UniformMat2()
{
}

void UniformMat2::updateData(const mat2& data)
{
	float x[] =
	{
		data[0][0], data[0][1], 0, 0,
		data[1][0], data[1][1], 0, 0
	};
	System::renderer->d3dDeviceContext->
		UpdateSubresource(buffer, 0, nullptr, &x, 0, 0);
}

void UniformMat2::bind()
{
	System::renderer->d3dDeviceContext->VSSetConstantBuffers(location, 1, &buffer);
	System::renderer->d3dDeviceContext->PSSetConstantBuffers(location, 1, &buffer);
}

}
#endif
