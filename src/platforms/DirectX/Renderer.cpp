#include "epc.h"
#ifdef R_D3D
#include "Platforms/Renderer.h"
#include "Platforms/ShaderProgram.h"
#include "Platforms/Window.h"
#include "Base/System.h"
#include "Base/Config.h"
#include "Platforms/VertexInterleavedBuffer.h"
#include "Platforms/IndexBuffer.h"
#include "Platforms/UniformMat2.h"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <DirectXTex/DirectXTex.h>

using namespace DirectX;
using namespace std;
HRESULT hr;


namespace glowy2d
{

Renderer::Renderer()
{
	if (!DirectX::XMVerifyCPUSupport())
		throw runtime_error("Failed to verify DirectX Math library support.");

	DXGI_MODE_DESC bufferDesc = { 0 };
	bufferDesc.Width = System::config->getScreenResolution().x;
	bufferDesc.Height = System::config->getScreenResolution().y;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc.Count = System::config->getAntialiasing();
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = System::window->getHandle();
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	D3D11CreateDeviceAndSwapChain(NULL, 
		D3D_DRIVER_TYPE_HARDWARE, 
		NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, 
		&swapChainDesc, 
		&d3dSwapChain, 
		&d3dDevice, 
		NULL, 
		&d3dDeviceContext);

	ID3D11Texture2D * backBuffer;
	hr = d3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	hr = d3dDevice->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	backBuffer->Release();

	D3D11_TEXTURE2D_DESC depthStencilDesc = { 0 };
	depthStencilDesc.Width = System::config->getScreenResolution().x;
	depthStencilDesc.Height = System::config->getScreenResolution().y;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = System::config->getAntialiasing();
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	d3dDevice->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	d3dDevice->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

	d3dDeviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);


	shaderProgram = new ShaderProgram("Effects.fx", "Effects.fx");
	shaderProgram->use();

	D3D11_VIEWPORT viewport = { 0 };
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = System::config->getScreenResolution().x;
	viewport.Height = System::config->getScreenResolution().y;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	d3dDeviceContext->RSSetViewports(1, &viewport);

	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.AntialiasedLineEnable = false;
	rasterizerDesc.CullMode				 = D3D11_CULL_BACK;
	rasterizerDesc.DepthBias			 = 0;
	rasterizerDesc.DepthBiasClamp		 = 0.0f;
	rasterizerDesc.DepthClipEnable		 = true;
	rasterizerDesc.FillMode				 = D3D11_FILL_SOLID;
	rasterizerDesc.FrontCounterClockwise = true;
	rasterizerDesc.MultisampleEnable	 = false;
	rasterizerDesc.ScissorEnable		 = false;
	rasterizerDesc.SlopeScaledDepthBias  = 0.0f;
	hr = d3dDevice->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
	d3dDeviceContext->RSSetState(rasterizerState);

	D3D11_BLEND_DESC blendStateDescription = { 0 };
	blendStateDescription.RenderTarget[0].BlendEnable = true;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	d3dDevice->CreateBlendState(&blendStateDescription, &alphaEnableBlendingState);
	float x[] = { 0.f, 0.f, 0.f, 0.f };
	d3dDeviceContext->OMSetBlendState(alphaEnableBlendingState, x, 0xffffffff);
	
	
	D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
		offsetof(vertex, position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
		offsetof(vertex, texture), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	shaderProgram->createInputLayout(vertexLayoutDesc);
	shaderProgram->setInputLayout();

	d3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	modelMatrixUniform = new UniformMat2(shaderProgram, "model", 0);
	modelMatrixUniform->bind();
	viewMatrixUniform = new UniformMat2(shaderProgram, "camera", 1);
	viewMatrixUniform->bind();
}

Renderer::~Renderer()
{
	delete shaderProgram;

	safeRelease(depthStencilView);
	safeRelease(renderTargetView);
	safeRelease(depthStencilBuffer);
	safeRelease(d3dDepthStencilState);
	safeRelease(rasterizerState);
	safeRelease(d3dSwapChain);
	safeRelease(d3dDeviceContext);
	safeRelease(d3dDevice);
	safeRelease(alphaEnableBlendingState);
}

void Renderer::clear()
{
	const float bgColor[4] = { (0.0f, 0.0f, 0.0f, 0.0f) };
	d3dDeviceContext->ClearRenderTargetView(renderTargetView, bgColor);
	d3dDeviceContext->ClearDepthStencilView(depthStencilView, 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Renderer::present(bool vSync)
{
	if (vSync)
		d3dSwapChain->Present(1, 0);
	else
		d3dSwapChain->Present(0, 0);
}

void Renderer::render()
{
	swapBuffers();
	pollEvents();
	present(System::config->getVSync());
}

void Renderer::setMatrix(const mat2& modelMatrix, const mat2& cameraMatrix)
{
	viewMatrixUniform->updateData(cameraMatrix);
	modelMatrixUniform->updateData(modelMatrix);
}

void Renderer::frameStart()
{
	clear();
}

void Renderer::draw(uint size)
{
	d3dDeviceContext->DrawIndexed(size, 0, 0);
}


void Renderer::pollEvents()
{
}

chrono::high_resolution_clock::time_point appStartTime = 
	chrono::high_resolution_clock::now();

double Renderer::getTime()
{
	chrono::high_resolution_clock::time_point now =
		chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::duration<double>>(now - appStartTime).count();
}

ID3D11Device		* Renderer::d3dDevice		 = nullptr;
ID3D11DeviceContext * Renderer::d3dDeviceContext = nullptr;
ID3D11InputLayout	* Renderer::d3dInputLayout	 = nullptr;

void Renderer::swapBuffers()
{
}

}
#endif