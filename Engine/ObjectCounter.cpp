#include "ObjectCounter.h"
#include <algorithm>

ObjectCounter::ObjectCounter(float min, float start, float factor, float speedy)
	: mMin(min), mStart(start), mPeriod(start), mFactor(factor), mSpeedy(speedy)
{
}

bool ObjectCounter::Tick(float dt, bool speedup)
{
	const bool ticked = (mCounter += dt) > (speedup ? std::min(mSpeedy, mPeriod) : mPeriod);

	if (ticked)
		mCounter = 0.0f;

	mPeriod = std::max(mPeriod - dt * mFactor, mMin);
	return ticked;
}

void ObjectCounter::Reset()
{
	mPeriod = mStart;
	mCounter = 0.0f;
}
