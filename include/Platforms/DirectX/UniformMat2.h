/****************************************************************************
This file is part of glowy3d.

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

struct ID3D11Buffer;
struct ID3D11ShaderReflection;

namespace glowy3d
{
	class ShaderProgram;

	class UniformMat2
	{
	public:
		UniformMat2(ShaderProgram * program, 
					const string& name, 
					unsigned location);
		UniformMat2(ShaderProgram * program, 
					const string& name, 
					unsigned location, 
					const mat2& data);
		~UniformMat2();

		void bind();

		void updateData(const mat2& data);

	private:
		uint location;
		
		ID3D11Buffer		   * buffer     = nullptr;
		ID3D11ShaderReflection * reflection = nullptr;
	};
}
#endif
