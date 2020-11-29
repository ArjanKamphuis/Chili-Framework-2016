#include "Poo.h"

Poo::Poo(const Vec2F& pos)
	: mPosition(pos)
{
}

void Poo::Draw(Graphics& gfx) const
{
	const Vec2I pos = static_cast<Vec2I>(mPosition + mDrawOffset);
	if (mEffectActive)
		gfx.DrawSprite(pos.X, pos.Y, mPoo, SpriteEffect::Substitution{ Colors::White, Colors::White });
	else
		gfx.DrawSprite(pos.X, pos.Y, mPoo, SpriteEffect::Chroma{ Colors::White });
}

void Poo::SetDirection(const Vec2F& dir)
{
	mVelocity = dir * mSpeed;
}

void Poo::Update(float dt)
{
	mPosition += mVelocity * dt;
	if (mEffectActive)
	{
		mEffectTime += dt;
		if (mEffectTime >= mEffectDuration)
			mEffectActive = false;
	}
}

void Poo::ActivateEffect()
{
	mEffectActive = true;
	mEffectTime = 0.0f;
}

const Vec2F& Poo::GetPosition() const
{
	return mPosition;
}
