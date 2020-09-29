#include "Brick.h"

Brick::Brick(const RectF& rect, Color c)
{
	mRect = rect;
	mColor = c;
}

void Brick::Draw(Graphics& gfx)
{
	gfx.DrawRect(mRect, mColor);
}
