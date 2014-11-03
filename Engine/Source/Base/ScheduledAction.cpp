#include "epc.h"
#include "Base/ScheduledAction.h"

namespace glowy2d
{
	ScheduledAction::ScheduledAction(std::function<void()> actionFunction, double delayTime) : Action(actionFunction), delay(delayTime), lastTimeUsed(0.0)
	{
	}

	void ScheduledAction::activateIfInTime(const double currentTime) const
	{
		if (currentTime - lastTimeUsed <= delay)
			Action::activate();
	}

	double ScheduledAction::getLastTimeUsed() const
	{
		return lastTimeUsed;
	}

	double ScheduledAction::getDelay() const
	{
		return delay;
	}

	void ScheduledAction::setDelay(const double newDelayTime)
	{
		delay = newDelayTime;
	}
}