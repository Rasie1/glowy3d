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
#pragma once
#ifdef R_D3D
#include "g2dMath.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11Texture2D;
struct ID3D11DepthStencilState;
struct ID3D11RasterizerState;
struct ID3D11InputLayout;

namespace glowy2d
{

class ShaderProgram;
class UniformMat2;

class Renderer
{
public:
	Renderer();
	~Renderer();

	static double getTime();
	void frameStart();
	void setMatrix(const mat2& modelMatrix, const mat2& cameraMatrix);
	void draw(uint size);
	void pollEvents();
	void render();

	void present(bool vSync);
	void clear();
	void swapBuffers();

	ShaderProgram * shaderProgram;

	static ID3D11Device		   * d3dDevice;
	static ID3D11DeviceContext * d3dDeviceContext;
	static ID3D11InputLayout   * d3dInputLayout;
private:
	IDXGISwapChain 		    * d3dSwapChain 			   = nullptr;
	ID3D11RenderTargetView  * renderTargetView 		   = nullptr;
	ID3D11DepthStencilView  * depthStencilView 	   	   = nullptr;
	ID3D11Texture2D         * depthStencilBuffer 	   = nullptr;
	ID3D11DepthStencilState * d3dDepthStencilState     = nullptr;
	ID3D11RasterizerState   * rasterizerState 		   = nullptr;
	ID3D11BlendState        * alphaEnableBlendingState = nullptr;
	
	UniformMat2	* modelMatrixUniform;
	UniformMat2	* viewMatrixUniform;
};

}
#endif