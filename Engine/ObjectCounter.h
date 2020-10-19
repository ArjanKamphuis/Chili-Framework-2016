#pragma once

class ObjectCounter
{
public:
	ObjectCounter(float min, float start, float factor);

	bool Tick(float dt);
	void Reset();

private:
	const float mMin;
	const float mStart;
	const float mFactor;
	float mPeriod;
	float mCounter = 0.0f;
};
