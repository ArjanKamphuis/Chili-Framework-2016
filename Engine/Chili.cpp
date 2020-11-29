#include "Chili.h"

Chili::Chili(const Vec2F& pos)
	: mPosition(pos)
{
	mAnimations.emplace_back(Animation(32, 0, 32, 33, 9, mLegs, 0.12f));
	mAnimations.emplace_back(Animation(0, 0, 32, 33, 1, mLegs, 10000.0f));
}

void Chili::Draw(Graphics& gfx) const
{
	const Vec2I drawpos = static_cast<Vec2I>(mPosition + mDrawOffset);
	const Vec2I legspos = drawpos + Vec2I{ 7, 40 };

	if (mEffectActive)
	{
		mAnimations[static_cast<int>(mCurrSequence)].DrawColor(gfx, legspos, Colors::Red, mFacingRight);
		gfx.DrawSprite(drawpos.X, drawpos.Y, mHead, SpriteEffect::Substitution{ Colors::Magenta, Colors::Red }, mFacingRight);
	}
	else
	{
		mAnimations[static_cast<int>(mCurrSequence)].Draw(gfx, legspos, mFacingRight);
		gfx.DrawSprite(drawpos.X, drawpos.Y, mHead, SpriteEffect::Chroma{ Colors::Magenta }, mFacingRight);
	}
}

void Chili::SetDirection(const Vec2F& dir)
{
	if (dir.X > 0.0f)
	{
		mCurrSequence = Sequence::Walking;
		mFacingRight = true;
	}
	else if (dir.X < 0.0f)
	{
		mCurrSequence = Sequence::Walking;
		mFacingRight = false;
	}
	else if (dir.Y != 0.0f)
		mCurrSequence = Sequence::Walking;
	else
		mCurrSequence = Sequence::Standing;

	mVelocity = dir * mSpeed;
}

void Chili::Update(float dt)
{
	mPosition += mVelocity * dt;
	mAnimations[static_cast<int>(mCurrSequence)].Update(dt);

	if (mEffectActive)
	{
		mEffectTime += dt;
		if (mEffectTime >= mEffectDuration)
			mEffectActive = false;
	}
}

void Chili::ActivateEffect()
{
	mEffectActive = true;
	mEffectTime = 0.0f;
}

const Vec2F& Chili::GetPosition() const
{
	return mPosition;
}

RectF Chili::GetHitbox() const
{
	return RectF::FromCenter(mPosition, mHitboxHalfWidth, mHitboxHalfHeight);
}
