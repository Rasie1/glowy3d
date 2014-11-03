#pragma once
#include "Base/IncludesEngine.h"
#include "Base/Action.h"
#include <functional>

namespace glowy2d
{
	class ScheduledAction : public Action
	{
	public:
		ScheduledAction(std::function<void()> actionFunction, double delayTime);

		void activateIfInTime(const double currentTime) const;

		double getLastTimeUsed() const;
		double getDelay() const;
		void setDelay(const double newDelayTime);

		~ScheduledAction() {}
	private:
		double delay;
		double lastTimeUsed;
	};
}