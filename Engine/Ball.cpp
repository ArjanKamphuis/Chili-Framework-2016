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
