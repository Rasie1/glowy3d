#pragma once
#include "Base/IncludesEngine.h"
#include "Base/Action.h"

#define MAX_SCHEDULES 512

namespace glowy2d
{
	class Scheduler
	{
	public:
		Scheduler() {}
		~Scheduler() {}

		void check(double currentTime);
		void add(Action * action, double delay);


	private:
		Action * actions[MAX_SCHEDULES];
		double   actionsLastTimeUsed[MAX_SCHEDULES];
		double   actionsDelays[MAX_SCHEDULES];
		unsigned actionsNum = 0;

	};
}
