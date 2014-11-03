#include "epc.h"
#include "Graphics/FramerateCounter.h"

namespace glowy2d
{
	FramerateCounter::FramerateCounter() :
		Action(std::bind(&FramerateCounter::printStatAndResetFrames, this))
	{
	}

	void FramerateCounter::countFrameStart(const double currentTime)
	{
		++frames;
		frameStartTime = currentTime;
	}

	void FramerateCounter::countFrameEnd(const double currentTime)
	{
		avgComputationalTime += currentTime - frameStartTime;
	}

	void FramerateCounter::printStatAndResetFrames()
	{
		printf("%d\\%f\n", getFrames(), getAvgComputationalTime());
		frames = 0;
		avgComputationalTime = 0.0;
	}

	unsigned FramerateCounter::getFrames() const
	{
		return frames;
	}

	double FramerateCounter::getAvgComputationalTime() const
	{
		return avgComputationalTime / (double)frames;
	}
}

/*
		nbFrames++;
		if (currentTime - lastTimeSecond >= 1.0f)
		{ // If last prinf() was more than 1 sec ago
			// printf and reset timer
			printf("TTD: %f\nFPS: %d\n", avgTimeToDraw / (double)nbFrames, nbFrames);
			nbFrames = 0;
			avgTimeToDraw = 0.0;
			lastTimeSecond = currentTime;
		}

		lastTime = currentTime;
*/