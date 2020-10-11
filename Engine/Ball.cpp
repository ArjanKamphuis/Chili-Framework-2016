#include "Ball.h"

#include "SpriteCodex.h"

Ball::Ball(const Vec2& pos, const Vec2& dir)
	: mPosition(pos)
{
	SetDirection(dir);
}

void Ball::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawBall(mPosition, gfx);
}

void Ball::Update(float dt)
{
	mPosition += mVelocity * dt;
}

int Ball::DoWallCollision(const RectF& walls)
{
	int collisionResult = 0;
	const RectF rect = GetRect();

	if (rect.Left < walls.Left)
	{
		mPosition.X += walls.Left - rect.Left;
		ReboundX();
		collisionResult = 1;
	}
	else if (rect.Right > walls.Right)
	{
		mPosition.X -= rect.Right - walls.Right;
		ReboundX();
		collisionResult = 1;
	}
	if (rect.Top < walls.Top)
	{
		mPosition.Y += walls.Top - rect.Top;
		ReboundY();
		collisionResult = 1;
	}
	else if (rect.Bottom > walls.Bottom)
	{
		mPosition.Y -= rect.Bottom - walls.Bottom;
		ReboundY();
		collisionResult = 2;
	}

	return collisionResult;
}

void Ball::ReboundX()
{
	mVelocity.X = -mVelocity.X;
}

void Ball::ReboundY()
{
	mVelocity.Y = -mVelocity.Y;
}

void Ball::SetDirection(const Vec2& dir)
{
	mVelocity = dir.GetNormalized() * mSpeed;
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter(mPosition, mRadius, mRadius);
}

Vec2 Ball::GetVelocity() const
{
	return mVelocity;
}

Vec2 Ball::GetPosition() const
{
	return mPosition;
}
