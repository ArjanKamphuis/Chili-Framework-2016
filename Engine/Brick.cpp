#include "Brick.h"

#include <assert.h>
#include <cmath>

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

bool Brick::CheckBallCollision(const Ball& ball) const
{
	return !mDestroyed && mRect.IsOverlappingWith(ball.GetRect());
}

void Brick::ExecuteBallCollision(Ball& ball)
{
	assert(CheckBallCollision(ball));

	const Vec2 ballPos = ball.GetPosition();
	if (std::signbit(ball.GetVelocity().X) == std::signbit((ballPos - GetCenter()).X))
		ball.ReboundY();
	else if (ballPos.X >= mRect.Left && ballPos.X <= mRect.Right)
		ball.ReboundY();
	else
		ball.ReboundX();

	mDestroyed = true;
}

Vec2 Brick::GetCenter() const
{
	return mRect.GetCenter();
}
