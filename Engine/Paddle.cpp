#include "Paddle.h"

#include <cmath>

Paddle::Paddle(const Vec2& pos, float halfWidth, float halfHeight)
	: mPosition(pos), mHalfWidth(halfWidth), mHalfHeight(halfHeight)
	, mExitXFactor(mMaxmimumExitRatio / halfWidth)
	, mFixedZoneHalfWidth(halfWidth * mFixedZoneWidthRatio)
	, mFixedZoneExitX(mFixedZoneHalfWidth * mExitXFactor)
{
}

void Paddle::Draw(Graphics& gfx) const
{
	RectF rect = GetRect();
	gfx.DrawRect(rect, mWingColor);

	rect.Left += mWingWidth;
	rect.Right -= mWingWidth;
	gfx.DrawRect(rect, mColor);
}

void Paddle::Update(Keyboard& kbd, float dt)
{
	if (kbd.KeyIsDown(VK_LEFT))
		mPosition.X -= mSpeed * dt;
	if (kbd.KeyIsDown(VK_RIGHT))
		mPosition.X += mSpeed * dt;
}

bool Paddle::DoBallCollision(Ball& ball)
{
	if (mIsOnCooldown)
		return false;

	const RectF rect = GetRect();
	if (rect.IsOverlappingWith(ball.GetRect()))
	{
		const Vec2 ballPos = ball.GetPosition();
		if ((std::signbit(ball.GetVelocity().X) == std::signbit((ballPos - mPosition).X)) || (ballPos.X >= rect.Left && ballPos.X <= rect.Right))
		{
			Vec2 dir;
			const float xDifference = ballPos.X - mPosition.X;

			if (std::abs(xDifference) < mFixedZoneHalfWidth)
			{
				if (xDifference < 0.0f)
					dir = Vec2(-mFixedZoneExitX, -1.0f);
				else
					dir = Vec2(mFixedZoneExitX, -1.0f);
			}
			else
				dir = Vec2(xDifference * mExitXFactor, -1.0f);

			ball.SetDirection(dir);
		}
		else
			ball.ReboundX();

		mIsOnCooldown = true;
		return true;
	}
	return false;
}

void Paddle::DoWallCollision(const RectF& walls)
{
	const RectF rect = GetRect();
	if (rect.Left < walls.Left)
		mPosition.X += walls.Left - rect.Left;
	else if (rect.Right > walls.Right)
		mPosition.X -= rect.Right - walls.Right;
}

void Paddle::ResetCooldown()
{
	mIsOnCooldown = false;
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(mPosition, mHalfWidth, mHalfHeight);
}
