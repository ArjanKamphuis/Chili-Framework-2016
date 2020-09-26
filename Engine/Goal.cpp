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
	int size = static_cast<int>(mSize);
	gfx.DrawRectDim(static_cast<int>(mPosition.X), static_cast<int>(mPosition.Y), size, size, Color(mR, mGB, mGB));
}
