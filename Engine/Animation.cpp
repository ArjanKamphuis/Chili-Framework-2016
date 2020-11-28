#include "Animation.h"
#include "SpriteEffect.h"

Animation::Animation(int x, int y, int width, int height, int count,const Surface& sprite, float holdTime, Color chroma)
	: mSprite(sprite), mHoldTime(holdTime), mChroma(chroma)
{
	for (int i = 0; i < count; ++i)
		mFrames.emplace_back(x + i * width, x + (i + 1) * width, y, y + height);
}

void Animation::Draw(Graphics& gfx, const Vec2I& pos) const
{
	//gfx.DrawSprite(pos.X, pos.Y, mFrames[mCurrFrame], mSprite, SpriteEffect::Ghost{ mChroma });

	// negative
	/*gfx.DrawSprite(pos.X, pos.Y, mFrames[mCurrFrame], mSprite,
		[this](Graphics& gfx, Color cSrc, int xDest, int yDest)
		{
			if (mChroma != cSrc)
				gfx.PutPixel(xDest, yDest, { 255u - cSrc.GetR(), 255u - cSrc.GetG(), 255u - cSrc.GetB() });
		}
	);*/

	// negative blend
	gfx.DrawSprite(pos.X, pos.Y, mFrames[mCurrFrame], mSprite,
		[this](Graphics& gfx, Color cSrc, int xDest, int yDest)
		{
			if (mChroma != cSrc)
			{
				const Color cDst = gfx.GetPixel(xDest, yDest);
				const Color blend = {
					static_cast<unsigned char>(((cDst.GetR() + cSrc.GetR()) / 2)),
					static_cast<unsigned char>(((cDst.GetG() + cSrc.GetG()) / 2)),
					static_cast<unsigned char>(((cDst.GetB() + cSrc.GetB()) / 2))
				};
				gfx.PutPixel(xDest, yDest, { 255u - blend.GetR(), 255u - blend.GetG(), 255u - blend.GetB() });
			}
		}
	);
}

void Animation::Draw(Graphics& gfx, const Vec2I& pos, const RectI& clip) const
{
	gfx.DrawSprite(pos.X, pos.Y, mFrames[mCurrFrame], clip, mSprite, SpriteEffect::Ghost{ mChroma });
}

void Animation::DrawColor(Graphics& gfx, const Vec2I& pos, Color c) const
{
	gfx.DrawSprite(pos.X, pos.Y, mFrames[mCurrFrame], mSprite, SpriteEffect::Substitution{ mChroma, c });
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
