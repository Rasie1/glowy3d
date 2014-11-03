#pragma once
#include "Base/IncludesEngine.h"
#include "Base/ScheduledAction.h"

namespace glowy2d
{
	class FramerateCounter : public Action
	{
	public:
		FramerateCounter();
		~FramerateCounter() {}

		void countFrameStart(const double currentTime);
		void countFrameEnd(const double timeOffset);

		void printStatAndResetFrames();

		unsigned getFrames() const;
		double getAvgComputationalTime() const;

	private:
		unsigned frames = 0;
		double avgComputationalTime = 0.0,
			frameStartTime;
	};
}