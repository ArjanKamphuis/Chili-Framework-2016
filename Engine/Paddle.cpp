#include "Paddle.h"

Paddle::Paddle(const Vec2& pos, float halfWidth, float halfHeight)
	: mPosition(pos), mHalfWidth(halfWidth), mHalfHeight(halfHeight)
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

bool Paddle::DoBallCollision(Ball& ball) const
{
	if (ball.GetVelocity().Y > 0.0f && GetRect().IsOverlappingWith(ball.GetRect()))
	{
		ball.ReboundY();
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

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(mPosition, mHalfWidth, mHalfHeight);
}
