#pragma once
#include "math/vertex.h"

namespace glowy3d
{

struct quad
{
	//top left
	vertex bl;
	//top right
	vertex br;
	//bottom right
	vertex tr;
	//bottom left
	vertex tl;

	quad(const vertex& one,   const vertex& two,
	     const vertex& three, const vertex& four);
	quad() {}

	void setDefaultCoords();
};

inline void quad::setDefaultCoords()
{
	*this = quad(
		vertex(0.f, 1.f, 0.f, 0.f, 1.f),
		vertex(0.f, 0.f, 0.f, 0.f, 0.f),
		vertex(1.f, 1.f, 0.f, 1.f, 1.f),
		vertex(1.f, 0.f, 0.f, 1.f, 0.f));
}

}
