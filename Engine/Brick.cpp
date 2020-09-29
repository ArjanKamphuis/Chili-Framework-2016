#include "Brick.h"

Brick::Brick(const RectF& rect, Color c)
{
	mRect = rect;
	mColor = c;
}

void Brick::Draw(Graphics& gfx) const
{
	if (!mDestroyed)
		gfx.DrawRect(mRect.GetExpanded(-mPadding), mColor);
}

bool Brick::DoBallCollision(Ball& ball)
{
	if (!mDestroyed && mRect.IsOverlappingWith(ball.GetRect()))
	{
		ball.ReboundY();
		mDestroyed = true;
		return true;
	}
	return false;
}
