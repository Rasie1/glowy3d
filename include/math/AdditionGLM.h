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
