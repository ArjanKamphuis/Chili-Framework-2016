#include "FrameTimer.h"

using namespace std::chrono;

float FrameTimer::Mark()
{
	const steady_clock::time_point old = mLast;
	mLast = steady_clock::now();
	const duration<float> frameTime = mLast - old;
	return frameTime.count();
}
