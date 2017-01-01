#pragma once
#include "base/Action.h"

#define MAX_SCHEDULES 512

namespace glowy3d
{

class Scheduler
{
public:
	void check(double currentTime);
	void add(Action* action, double delay);

private:
	Action*  actions[MAX_SCHEDULES];
	double   actionsLastTimeUsed[MAX_SCHEDULES];
	double   actionsDelays[MAX_SCHEDULES];
	unsigned actionsNum = 0;

};

}
