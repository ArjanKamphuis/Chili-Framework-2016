#include "Bullet.h"

Bullet::Bullet(const Vec2F& pos, const Vec2F& dir)
	: mPosition(pos), mVelocity(dir * mSpeed)
{
}

Bullet::Bullet(const Bullet& rhs)
	: mBullet(rhs.mBullet), mBulletAnimation(0, 0, 8, 8, 4, mBullet, 0.1f), mPosition(rhs.mPosition), mVelocity(rhs.mVelocity)
{
}

Bullet& Bullet::operator=(const Bullet& rhs)
{
	if (this != &rhs)
	{
		mPosition = rhs.mPosition;
		mVelocity = rhs.mVelocity;
	}
	return *this;
}

void Bullet::Draw(Graphics& gfx) const
{
	mBulletAnimation.Draw(gfx, static_cast<Vec2I>(mPosition + mDrawOffset));
}

void Bullet::Update(float dt)
{
	mPosition += mVelocity * dt;
	mBulletAnimation.Update(dt);
}

const Vec2F& Bullet::GetPosition() const
{
	return mPosition;
}

RectF Bullet::GetHitbox() const
{
	return RectF::FromCenter(mPosition, mHitboxHalfWidth, mHitboxHalfHeight);
}
