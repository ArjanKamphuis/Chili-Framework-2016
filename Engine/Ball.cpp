#include "Ball.h"

#include "SpriteCodex.h"

Ball::Ball(const Vec2& pos, const Vec2& vel)
	: mPosition(pos), mVelocity(vel)
{
}

void Ball::Draw(Graphics& gfx)
{
	SpriteCodex::DrawBall(mPosition, gfx);
}

void Ball::Update(float dt)
{
	mPosition += mVelocity * dt;
}

bool Ball::DoWallCollision(const RectF& walls)
{
	bool collided = false;
	const RectF rect = GetRect();

	if (rect.Left < walls.Left)
	{
		mPosition.X += walls.Left - rect.Left;
		ReboundX();
		collided = true;
	}
	else if (rect.Right > walls.Right)
	{
		mPosition.X -= rect.Right - walls.Right;
		ReboundX();
		collided = true;
	}
	if (rect.Top < walls.Top)
	{
		mPosition.Y += walls.Top - rect.Top;
		ReboundY();
		collided = true;
	}
	else if (rect.Bottom > walls.Bottom)
	{
		mPosition.Y -= rect.Bottom - walls.Bottom;
		ReboundY();
		collided = true;
	}

	return collided;
}

void Ball::ReboundX()
{
	mVelocity.X = -mVelocity.X;
}

void Ball::ReboundY()
{
	mVelocity.Y = -mVelocity.Y;
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter(mPosition, mRadius, mRadius);
}
