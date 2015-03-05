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

#include "glm/glm.hpp"
#include "glm/detail/precision.hpp"
#include "glm/detail/type_int.hpp"

namespace glm
{

/// Additional types for short, char, unsigned short and unsigned char vectors
typedef tvec2<unsigned short, highp>	highp_usvec2;
typedef tvec2<unsigned short, mediump>	mediump_usvec2;
typedef tvec2<unsigned short, lowp>		lowp_usvec2;

typedef tvec2<unsigned char, highp>		highp_ucvec2;
typedef tvec2<unsigned char, mediump>	mediump_ucvec2;
typedef tvec2<unsigned char, lowp>		lowp_ucvec2;

typedef tvec2<short, highp>		highp_svec2;
typedef tvec2<short, mediump>	mediump_svec2;
typedef tvec2<short, lowp>		lowp_svec2;

typedef tvec2<char, highp>		highp_cvec2;
typedef tvec2<char, mediump>	mediump_cvec2;
typedef tvec2<char, lowp>		lowp_cvec2;

typedef tvec3<char, highp>		highp_cvec3;
typedef tvec3<char, mediump>	mediump_cvec3;
typedef tvec3<char, lowp>		lowp_cvec3;

typedef tvec3<unsigned char, highp>		highp_ucvec3;
typedef tvec3<unsigned char, mediump>	mediump_ucvec3;
typedef tvec3<unsigned char, lowp>		lowp_ucvec3;

typedef tvec4<char, highp>		highp_cvec4;
typedef tvec4<char, mediump>	mediump_cvec4;
typedef tvec4<char, lowp>		lowp_cvec4;

typedef tvec4<unsigned char, highp>		highp_ucvec4;
typedef tvec4<unsigned char, mediump>	mediump_ucvec4;
typedef tvec4<unsigned char, lowp>		lowp_ucvec4;

typedef highp_cvec2 cvec2;
typedef highp_ucvec2 ucvec2;
typedef highp_svec2 svec2;
typedef highp_usvec2 usvec2;
typedef highp_cvec3 cvec3;
typedef highp_ucvec3 ucvec3;
typedef highp_cvec4 cvec4;
typedef highp_ucvec4 ucvec4;

typedef unsigned char ubyte;

}