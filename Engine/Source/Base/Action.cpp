#include "epc.h"
#include "Base/Action.h"

namespace glowy2d
{
	void Action::activate() const
	{
		action();
	}
}