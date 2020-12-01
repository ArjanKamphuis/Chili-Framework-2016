#include "Poo.h"

Poo::Poo(const Vec2F& pos)
	: mPosition(pos)
{
}

void Poo::Draw(Graphics& gfx) const
{
	const Vec2I pos = static_cast<Vec2I>(mPosition + mDrawOffset);
	switch (mEffectState)
	{
	case EffectState::Hit:
		gfx.DrawSprite(pos.X, pos.Y, mPoo, SpriteEffect::Substitution{ Colors::White, Colors::White });
		break;
	case EffectState::Dying:
		gfx.DrawSprite(pos.X, pos.Y, mPoo, SpriteEffect::DissolveHalfTint{ Colors::White, Colors::Red, 1.0f - mEffectTime / mDissolveDuration });
		break;
	case EffectState::Normal:
		gfx.DrawSprite(pos.X, pos.Y, mPoo, SpriteEffect::Chroma{ Colors::White });
		break;
	}
}

void Poo::SetDirection(const Vec2F& dir)
{
	mVelocity = dir * mSpeed;
}

void Poo::Update(float dt)
{
	if (!IsDead())
		mPosition += mVelocity * dt;

	mEffectTime += dt;

	switch (mEffectState)
	{
	case EffectState::Hit:
		if (mEffectTime >= mHitFlashDuration)
		{
			if (IsDead())
			{
				mEffectState = EffectState::Dying;
				mEffectTime = 0.0f;
			}
			else
				mEffectState = EffectState::Normal;
		}
		break;
	case EffectState::Dying:
		if (mEffectTime >= mDissolveDuration)
			mIsReadyForRemoval = true;
		break;
	}
}

void Poo::ApplyDamage(float damage)
{
	mHp -= static_cast<int>(damage);
	mEffectState = EffectState::Hit;
	mEffectTime = 0.0f;
}

bool Poo::IsDead() const
{
	return mHp <= 0;
}

bool Poo::IsReadyForRemoval() const
{
	return mIsReadyForRemoval;
}

const Vec2F& Poo::GetPosition() const
{
	return mPosition;
}

RectF Poo::GetHitbox() const
{
	return RectF::FromCenter(mPosition, mHitboxHalfWidth, mHitboxHalfHeight);
}
