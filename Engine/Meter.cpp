#include "Meter.h"

Meter::Meter(int x, int y)
	: mPosition{ x, y }
{
}

void Meter::IncreaseLevel()
{
	++mLevel;
}

void Meter::ResetLevel()
{
	mLevel = 0;
}

void Meter::Draw(Graphics& gfx) const
{
	gfx.DrawRectDim(mPosition.x, mPosition.y, mLevel * mScale, mGirth, mColor);
}
