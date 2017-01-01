#include "math/quad.h"

using namespace std;

namespace glowy3d
{

quad::quad(const vertex& one,   const vertex& two,
		   const vertex& three, const vertex& four) :
		   tl(one),
		   tr(two),
		   br(three),
		   bl(four)
{

}

}
