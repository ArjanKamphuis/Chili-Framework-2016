#pragma once

class ObjectCounter
{
public:
	ObjectCounter(float min, float start, float factor, float speedy = 0.0f);

	bool Tick(float dt, bool speedup = false);
	void Reset();

private:
	const float mMin;
	const float mStart;
	const float mFactor;
	const float mSpeedy;
	float mPeriod;
	float mCounter = 0.0f;
};
