#include "graphics/FramerateCounter.h"
#include <iostream> 
#include "platforms/Window.h"
#include "base/System.h"

using namespace std;

namespace glowy3d
{

FramerateCounter::FramerateCounter() :
	Action(std::bind(&FramerateCounter::printStatAndResetFrames, this))
{
}

void FramerateCounter::countFrameStart(double currentTime)
{
	++frames;
	frameStartTime = currentTime;
}

void FramerateCounter::countFrameEnd(double currentTime)
{
	avgComputationalTime += currentTime - frameStartTime;
}

void FramerateCounter::printStatAndResetFrames()
{
	char str[79]; // max window text length
	sprintf(str, "%d\\%f\n", getFrames(), getAvgComputationalTime());
	cout << str << endl;
	System::window->setText(str);

	frames = 0;
	avgComputationalTime = 0.0;
}

unsigned FramerateCounter::getFrames() const
{
	return frames;
}

double FramerateCounter::getAvgComputationalTime() const
{
	return avgComputationalTime / static_cast<double>(frames);
}

}
