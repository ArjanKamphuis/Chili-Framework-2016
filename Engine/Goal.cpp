#include "Goal.h"

Goal::Goal()
	: GameObject(20)
{
}

void Goal::Update()
{
	if (mColorIncrease)
	{
		mR += mColorSpeed;
		mGB += 2 * mColorSpeed;
		if (mR >= 253)
			mColorIncrease = false;
	}
	else
	{
		mR -= mColorSpeed;
		mGB -= 2 * mColorSpeed; 
		if (mR <= 127)
			mColorIncrease = true;
	}
}

void Goal::Draw(Graphics& gfx) const
{
	gfx.DrawRectDim(mPosition.x, mPosition.y, mSize, mSize, Color(mR, mGB, mGB));
}
