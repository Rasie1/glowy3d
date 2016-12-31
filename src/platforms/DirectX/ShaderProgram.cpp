#include "epc.h"
#ifdef R_D3D
#include "Platforms/ShaderProgram.h"
#include <string>
#include <fstream>
#include <vector>
#include "Platforms/Renderer.h"
#include "Math/vertex.h"
#include "Platforms/VertexInterleavedBuffer.h"


template<class ShaderClass>
std::string GetLatestProfile();

template<>
std::string GetLatestProfile<ID3D11VertexShader>()
{
	assert(glowy2d::Renderer::d3dDevice);

	// Query the current feature level:
	D3D_FEATURE_LEVEL featureLevel = glowy2d::Renderer::d3dDevice->GetFeatureLevel();

	switch (featureLevel)
	{
	case D3D_FEATURE_LEVEL_11_1:
	case D3D_FEATURE_LEVEL_11_0:
	{
								   return "vs_5_0";
	}
		break;
	case D3D_FEATURE_LEVEL_10_1:
	{
								   return "vs_4_1";
	}
		break;
	case D3D_FEATURE_LEVEL_10_0:
	{
								   return "vs_4_0";
	}
		break;
	case D3D_FEATURE_LEVEL_9_3:
	{
								  return "vs_4_0_level_9_3";
	}
		break;
	case D3D_FEATURE_LEVEL_9_2:
	case D3D_FEATURE_LEVEL_9_1:
	{
								  return "vs_4_0_level_9_1";
	}
		break;
	} // switch( featureLevel )

	return "";
}

template<>
std::string GetLatestProfile<ID3D11PixelShader>()
{
	assert(glowy2d::Renderer::d3dDevice);

	// Query the current feature level:
	D3D_FEATURE_LEVEL featureLevel = 
		glowy2d::Renderer::d3dDevice->GetFeatureLevel();
	switch (featureLevel)
	{
	case D3D_FEATURE_LEVEL_11_1:
	case D3D_FEATURE_LEVEL_11_0:
	{
								   return "ps_5_0";
	}
		break;
	case D3D_FEATURE_LEVEL_10_1:
	{
								   return "ps_4_1";
	}
		break;
	case D3D_FEATURE_LEVEL_10_0:
	{
								   return "ps_4_0";
	}
		break;
	case D3D_FEATURE_LEVEL_9_3:
	{
								  return "ps_4_0_level_9_3";
	}
		break;
	case D3D_FEATURE_LEVEL_9_2:
	case D3D_FEATURE_LEVEL_9_1:
	{
								  return "ps_4_0_level_9_1";
	}
		break;
	}
	return "";
}


std::string readFile(const char * filePath)
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open())
	{
		std::cout << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

using namespace std;

namespace glowy2d
{

ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath)
{

	HRESULT hr;
	ID3D10Blob * errorBlob;

	hr = D3DCompileFromFile(
		std::wstring(begin(vertexPath), end(vertexPath)).c_str(),
		0, 0,
		"VS",
		"vs_4_0",
		0, 0,
		&vsBufferBlob,
		&errorBlob);

	if (FAILED(hr))
		reportErrors();

	hr = D3DCompileFromFile(
		std::wstring(begin(fragmentPath), end(fragmentPath)).c_str(),
		0, 0,
		"PS",
		"ps_4_0",
		0, 0,
		&psBufferBlob,
		&errorBlob);

	if (FAILED(hr))
		reportErrors();

	hr = Renderer::d3dDevice->CreateVertexShader(vsBufferBlob->GetBufferPointer(), vsBufferBlob->GetBufferSize(), NULL, &vertexShader);
	if (FAILED(hr))
		throw exception("[DX11]Failed to create vertex shader");

	hr = Renderer::d3dDevice->CreatePixelShader(psBufferBlob->GetBufferPointer(), psBufferBlob->GetBufferSize(), NULL, &pixelShader);
	if (FAILED(hr))
		throw exception("[DX11]Failed to create pixel shader");
}

ShaderProgram::~ShaderProgram()
{
	safeRelease(vsBufferBlob);
	safeRelease(psBufferBlob);
	safeRelease(vertexShader);
	safeRelease(pixelShader);
}

void ShaderProgram::createInputLayout(D3D11_INPUT_ELEMENT_DESC * desc)
{
	Renderer::d3dDevice->CreateInputLayout(
		desc,
		2,
		vsBufferBlob->GetBufferPointer(),
		vsBufferBlob->GetBufferSize(),
		&Renderer::d3dInputLayout);
}

void ShaderProgram::setInputLayout()
{
	Renderer::d3dDeviceContext->IASetInputLayout(Renderer::d3dInputLayout);
}

void ShaderProgram::reportErrors()
{
	if (errorBlob)
	{
		std::string errorMessage = (char*)errorBlob->GetBufferPointer();
		OutputDebugStringA(errorMessage.c_str());

		throw exception("Shader couldn't be loaded");
	}

}

void ShaderProgram::use()
{
	Renderer::d3dDeviceContext->VSSetShader(vertexShader, nullptr, 0);
	Renderer::d3dDeviceContext->PSSetShader(pixelShader, nullptr, 0);
}

}
#endif