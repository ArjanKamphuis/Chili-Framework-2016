#include "ObjectCounter.h"
#include <algorithm>

ObjectCounter::ObjectCounter(float min, float start, float factor)
	: mMin(min), mStart(start), mPeriod(start), mFactor(factor)
{
}

bool ObjectCounter::Tick(float dt)
{
	const bool ticked = (mCounter += dt) > mPeriod;

	if (ticked)
		mCounter -= mPeriod;

	mPeriod = std::max(mPeriod - dt * mFactor, mMin);
	return ticked;
}

void ObjectCounter::Reset()
{
	mPeriod = mStart;
	mCounter = 0.0f;
}
