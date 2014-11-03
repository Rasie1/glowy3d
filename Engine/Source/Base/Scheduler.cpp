#include "epc.h"
#include "Base/Scheduler.h"

namespace glowy2d
{
	void Scheduler::check(double currentTime)
	{
		for (uint i = 0; i < actionsNum; ++i)
		if (currentTime - actionsLastTimeUsed[i] >= actionsDelays[i])
		{
			actions[i]->activate();
			actionsLastTimeUsed[i] = currentTime;
		}
	}

	void Scheduler::add(Action * action, double delay)
	{
		actions[actionsNum] = action;
		actionsDelays[actionsNum] = delay;

		++actionsNum;
	}
}