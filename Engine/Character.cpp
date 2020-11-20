#include "Character.h"

Character::Character(const Vec2F& pos)
	: mPosition(pos)
{
	const int walkingCount = static_cast<int>(Sequence::StandingLeft);
	for (int i = 0; i < walkingCount; ++i)
		mAnimations.emplace_back(Animation(90, 90 * i, 90, 90, 4, mSprite, 0.16f));
	for (int i = walkingCount; i < static_cast<int>(Sequence::Count); ++i)
		mAnimations.emplace_back(Animation(0, 90 * (i - walkingCount), 90, 90, 1, mSprite, 0.16f));
}

void Character::Update(float dt)
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

void Character::Draw(Graphics& gfx) const
{
	if (mEffectActive)
		mAnimations[static_cast<int>(mCurrSequence)].DrawColor(gfx, static_cast<Vec2I>(mPosition), Colors::Red);
	else
		mAnimations[static_cast<int>(mCurrSequence)].Draw(gfx, static_cast<Vec2I>(mPosition));
}

void Character::SetDirection(const Vec2F& dir)
{
	if (dir.X > 0.0f)
		mCurrSequence = Sequence::WalkingRight;
	else if (dir.X < 0.0f)
		mCurrSequence = Sequence::WalkingLeft;
	else if (dir.Y < 0.0f)
		mCurrSequence = Sequence::WalkingUp;
	else if (dir.Y > 0.0f)
		mCurrSequence = Sequence::WalkingDown;
	else
	{
		if (mVelocity.X > 0.0f)
			mCurrSequence = Sequence::StandingRight;
		else if (mVelocity.X < 0.0f)
			mCurrSequence = Sequence::StandingLeft;
		else if (mVelocity.Y < 0.0f)
			mCurrSequence = Sequence::StandingUp;
		else if (mVelocity.Y > 0.0f)
			mCurrSequence = Sequence::StandingDown;
	}

	mVelocity = dir * mSpeed;
}

void Character::ActivateEffect()
{
	mEffectActive = true;
	mEffectTime = 0.0f;
}
