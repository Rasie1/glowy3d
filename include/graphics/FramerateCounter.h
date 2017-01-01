#pragma once
#include "base/ScheduledAction.h"

namespace glowy3d
{

class FramerateCounter : public Action
{
public:
	FramerateCounter();

	void countFrameStart(double currentTime);
	void countFrameEnd(double timeOffset);

	void printStatAndResetFrames();

	unsigned getFrames() const;
	double   getAvgComputationalTime() const;

private:
	unsigned frames = 0;
	double avgComputationalTime = 0.0,
		   frameStartTime;
};

}
