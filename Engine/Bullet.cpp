#include "Bullet.h"

Bullet::Bullet(const Vec2F& pos, const Vec2F& dir)
	: mPosition(pos), mVelocity(dir * mSpeed)
{
}

void Bullet::Draw(Graphics& gfx) const
{
	mBulletAnimation.Draw(gfx, static_cast<Vec2I>(mPosition + mDrawOffset));
}

void Bullet::Update(float dt)
{
	mPosition += mVelocity * dt;
}

const Vec2F& Bullet::GetPosition() const
{
	return mPosition;
}

RectF Bullet::GetHitbox() const
{
	return RectF::FromCenter(mPosition, mHitboxHalfWidth, mHitboxHalfHeight);
}
