#include "Animation.h"

Animation::Animation(int x, int y, int width, int height, int count,const Surface& sprite, float holdTime, Color chroma)
	: mSprite(sprite), mHoldTime(holdTime), mChroma(chroma)
{
	for (int i = 0; i < count; ++i)
		mFrames.emplace_back(x + i * width, x + (i + 1) * width, y, y + height);
}

void Animation::Draw(Graphics& gfx, const Vec2I& pos) const
{
	gfx.DrawSprite(pos.X, pos.Y, mFrames[mCurrFrame], mSprite, mChroma);
}

void Animation::Draw(Graphics& gfx, const Vec2I& pos, const RectI& clip) const
{
	gfx.DrawSprite(pos.X, pos.Y, mFrames[mCurrFrame], clip, mSprite, mChroma);
}

void Animation::Update(float dt)
{
	mCurrFrameTime += dt;
	while (mCurrFrameTime >= mHoldTime)
	{
		Advance();
		mCurrFrameTime -= mHoldTime;
	}
}

void Animation::Advance()
{
	if (++mCurrFrame >= static_cast<int>(mFrames.size()))
		mCurrFrame = 0;
}
