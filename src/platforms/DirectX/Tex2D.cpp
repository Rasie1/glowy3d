/****************************************************************************
This file is part of glowy2d.

Copyright (c) 2014 Kvachev 'Rasie1' V. D.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "epc.h"
#ifdef R_D3D
#include "Base/System.h"
#include "Graphics/TextureData.h"
#include "Platforms/Tex2D.h"
#include "Platforms/Renderer.h"

using namespace std;

namespace glowy2d
{

Tex2D::Tex2D(TextureData * data) :
	size(data->resolution)
{
	D3D11_SUBRESOURCE_DATA textureSubresourceData = { 0 };
	textureSubresourceData.pSysMem = data->data;
	textureSubresourceData.SysMemPitch = data->resolution.x * 4;
	textureSubresourceData.SysMemSlicePitch = 0;

	D3D11_TEXTURE2D_DESC textureDesc = { 0 };
	textureDesc.Width = data->resolution.x;
	textureDesc.Height = data->resolution.y;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	System::renderer->d3dDevice->CreateTexture2D(
		&textureDesc,
		&textureSubresourceData,
		&texture);

	D3D11_SHADER_RESOURCE_VIEW_DESC textureViewDesc;
	ZeroMemory(&textureViewDesc, sizeof(textureViewDesc));
	textureViewDesc.Format = textureDesc.Format;
	textureViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	textureViewDesc.Texture2D.MipLevels = textureDesc.MipLevels;
	textureViewDesc.Texture2D.MostDetailedMip = 0;

	System::renderer->d3dDevice->CreateShaderResourceView(
		texture,
		&textureViewDesc,
		&textureView
		);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter   = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	System::renderer->d3dDevice->CreateSamplerState(&sampDesc, &textureSamplerState);
}

void Tex2D::bind()
{
	System::renderer->d3dDeviceContext->PSSetShaderResources(0, 1, &textureView);
	System::renderer->d3dDeviceContext->PSSetSamplers(0, 1, &textureSamplerState);
}

Tex2D::Tex2D(const char * filename) : Tex2D(TextureData::load(filename))
{
}

Tex2D::~Tex2D()
{
}

void Tex2D::release()
{
}

void Tex2D::pixelsReplace(TextureData * data, usvec2 offset)
{
	bind();
	D3D11_BOX box;
	box.left = offset.x;
	box.top = offset.y;
	box.right = data->resolution.x + offset.x;
	box.bottom = data->resolution.y + offset.y;
	box.front = 0;
	box.back = 1;
	System::renderer->d3dDeviceContext->UpdateSubresource(
		texture, 
		0, 
		&box, 
		data->data, 
		data->resolution.x * 4, 
		data->resolution.x * data->resolution.y * 4);
}

}
#endif