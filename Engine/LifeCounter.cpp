#include "LifeCounter.h"

#include <algorithm>
#include "SpriteCodex.h"

LifeCounter::LifeCounter(Vec2 pos, int lives)
	: mPos(pos), mLives(lives)
{
}

bool LifeCounter::ConsumeLife()
{
	const bool hasLife = mLives > 0;
	mLives = max(mLives - 1, 0);
	return hasLife;
}

void LifeCounter::Draw(Graphics& gfx) const
{
	const Vec2 offset(mSpacing, 0.0f);
	for (int c = 0; c < mLives; ++c)
		SpriteCodex::DrawPoo(mPos + offset * static_cast<float>(c), gfx);
}
