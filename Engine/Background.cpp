#include "Background.h"

#include "SpriteEffect.h"

Background::Background(const RectI& bgRegion, int gridWidth, int gridHeight, const std::string& map)
	: mOrigin(bgRegion.TopLeft()), mGridWidth(gridWidth), mGridHeight(gridHeight)
{
	for (int i = 0; i < mNumTiles; ++i)
		mTileRects.emplace_back(Vec2I{ mTileSize, 0 } * i, mTileSize, mTileSize);

	mTiles.reserve(static_cast<size_t>(mGridWidth) * mGridHeight);
	auto mi = map.cbegin();
	for (int i = 0; i < mGridWidth * mGridHeight; ++i, ++mi)
		mTiles.push_back(*mi - 'B');
}

void Background::Draw(Graphics& gfx) const
{
	for (int y = 0; y < mGridHeight; ++y)
	{
		for (int x = 0; x < mGridWidth; ++x)
		{
			const int index = GetTileAt(x, y);
			if (index >= 0)
				gfx.DrawSprite(x * mTileSize + mOrigin.X, y * mTileSize + mOrigin.Y, mTileRects[index], *mTilesetSurface, SpriteEffect::Copy{});
		}
	}
}

int Background::GetTileAt(int x, int y) const
{
	return mTiles[static_cast<size_t>(y) * mGridWidth + x];
}
