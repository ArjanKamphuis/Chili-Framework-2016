#include "Chili.h"

Chili::DamageEffectController::DamageEffectController(const Chili& parent)
	: mParent(parent)
{
}

void Chili::DamageEffectController::Update(float dt)
{
	if (mActive)
	{
		mTime += dt;
		if (mTime >= mTotalDuration)
			mActive = false;
	}
}

void Chili::DamageEffectController::DrawChili(Graphics& gfx) const
{
	const Vec2I drawpos = static_cast<Vec2I>(mParent.mPosition + mParent.mDrawOffset);
	const Vec2I legspos = drawpos + Vec2I{ 7, 40 };

	if (mActive)
	{
		if (mTime <= mRedDuration)
		{
			mParent.mAnimations[static_cast<int>(mParent.mCurrSequence)].DrawColor(gfx, legspos, Colors::Red, mParent.mFacingRight);
			gfx.DrawSprite(drawpos.X, drawpos.Y, *mParent.mHeadSurface, SpriteEffect::Substitution{ Colors::Magenta, Colors::Red }, mParent.mFacingRight);
		}
		else
		{
			if (static_cast<int>(mTime / mBlinkHalfPeriod) % 2 != 0)
			{
				mParent.mAnimations[static_cast<int>(mParent.mCurrSequence)].Draw(gfx, legspos, mParent.mFacingRight);
				gfx.DrawSprite(drawpos.X, drawpos.Y, *mParent.mHeadSurface, SpriteEffect::Chroma{ Colors::Magenta }, mParent.mFacingRight);
			}
		}
	}
	else
	{
		mParent.mAnimations[static_cast<int>(mParent.mCurrSequence)].Draw(gfx, legspos, mParent.mFacingRight);
		gfx.DrawSprite(drawpos.X, drawpos.Y, *mParent.mHeadSurface, SpriteEffect::Chroma{ Colors::Magenta }, mParent.mFacingRight);
	}
}

void Chili::DamageEffectController::Activate()
{
	if (!mActive)
	{
		mActive = true;
		mTime = 0.0f;
	}
}

bool Chili::DamageEffectController::IsActive() const
{
	return mActive;
}

Chili::Chili(const Vec2F& pos)
	: mPosition(pos)
{
	const Surface* pLegsSurface = Codex<Surface>::Retreive(L"Images/legs-skinny.bmp");

	mAnimations.emplace_back(Animation(32, 0, 32, 33, 9, pLegsSurface, 0.12f));
	mAnimations.emplace_back(Animation(0, 0, 32, 33, 1, pLegsSurface, 10000.0f));
}

void Chili::Draw(Graphics& gfx) const
{
	mDamageEffectController.DrawChili(gfx);
}

void Chili::SetDirection(const Vec2F& dir)
{
	if (dir.X > 0.0f)
	{
		mCurrSequence = AnimationSequence::Walking;
		mFacingRight = true;
	}
	else if (dir.X < 0.0f)
	{
		mCurrSequence = AnimationSequence::Walking;
		mFacingRight = false;
	}
	else if (dir.Y != 0.0f)
		mCurrSequence = AnimationSequence::Walking;
	else
		mCurrSequence = AnimationSequence::Standing;

	mVelocity = dir * mSpeed;
}

void Chili::Update(float dt)
{
	mPosition += mVelocity * dt;
	mAnimations[static_cast<int>(mCurrSequence)].Update(dt);
	mDamageEffectController.Update(dt);
}

void Chili::DisplaceBy(const Vec2F& d)
{
	mPosition += d;
}

void Chili::ApplyDamage()
{
	mDamageEffectController.Activate();
}

bool Chili::IsInvincible() const
{
	return mDamageEffectController.IsActive();
}

const Vec2F& Chili::GetPosition() const
{
	return mPosition;
}

RectF Chili::GetHitbox() const
{
	return RectF::FromCenter(mPosition, mHitboxHalfWidth, mHitboxHalfHeight);
}
