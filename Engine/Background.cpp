#include "Background.h"
#include "SpriteEffect.h"

Background::Background(const RectI& rect)
	: mOrigin(rect.TopLeft())
	, mGridWidth(div_int_ceil(rect.GetWidth(), mFloor.GetWidth()))
	, mGridHeight(div_int_ceil(rect.GetHeight(), mFloor.GetHeight()))
{
}

void Background::Draw(Graphics& gfx) const
{
	const int tileWidth = mFloor.GetWidth();
	const int tileHeight = mFloor.GetHeight();
	for (int y = 0; y < mGridHeight; ++y)
		for (int x = 0; x < mGridWidth; ++x)
			gfx.DrawSprite(x * tileWidth + mOrigin.X, y * tileHeight + mOrigin.Y, mFloor, SpriteEffect::Copy{});
}
