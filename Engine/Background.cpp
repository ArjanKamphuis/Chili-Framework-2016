#include "Background.h"

#include <random>
#include "SpriteEffect.h"

Background::Background(const RectI& bgRegion)
	: mOrigin(bgRegion.TopLeft())
	, mGridWidth(div_int_ceil(bgRegion.GetWidth(), mTileSize))
	, mGridHeight(div_int_ceil(bgRegion.GetHeight(), mTileSize))
{
	for (int i = 0; i < mNumTiles; ++i)
		mTileRects.emplace_back(Vec2I{ mTileSize, 0 } * i, mTileSize, mTileSize);

	mTiles.reserve(static_cast<size_t>(mGridWidth * mGridHeight));
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, mNumTiles - 1);
	for (int i = 0; i < mGridWidth * mGridHeight; ++i)
		mTiles.push_back(dist(rng));
}

void Background::Draw(Graphics& gfx) const
{
	for (int y = 0; y < mGridHeight; ++y)
		for (int x = 0; x < mGridWidth; ++x)
			gfx.DrawSprite(x * mTileSize + mOrigin.X, y * mTileSize + mOrigin.Y, mTileRects[GetTileAt(x, y)], mTileset, SpriteEffect::Copy{});
}

int Background::GetTileAt(int x, int y) const
{
	return mTiles[static_cast<size_t>(y * mGridWidth + x)];
}
