#include "base/ScheduledAction.h"

using namespace std;

namespace glowy3d
{

ScheduledAction::ScheduledAction(std::function<void()> actionFunction, double delayTime) : 
	Action(actionFunction), 
	delay(delayTime), 
	lastTimeUsed(0.0)
{
}

void ScheduledAction::activateIfInTime(double currentTime) const
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

void ScheduledAction::setDelay(double newDelayTime)
{
	delay = newDelayTime;
}

}
