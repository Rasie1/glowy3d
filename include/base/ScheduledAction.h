#pragma once
#include "base/Action.h"
#include <functional>

namespace glowy3d
{

class ScheduledAction : public Action
{
public:
	ScheduledAction(std::function<void()> actionFunction, double delayTime);

	void activateIfInTime(double currentTime) const;

	double getLastTimeUsed() const;
	double getDelay() const;
	void   setDelay(double newDelayTime);

private:
	double delay;
	double lastTimeUsed;
};

}
