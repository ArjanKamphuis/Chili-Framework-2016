#include "MemeField.h"

#include <assert.h>
#include <random>
#include "Vec2I.h"
#include "SpriteCodex.h"

MemeField::MemeField(int nMemes)
{
	assert(nMemes > 0 && nMemes < mWidth* mHeight);

	std::mt19937 rng = std::mt19937(std::random_device()());
	std::uniform_int_distribution<int> xDist(0, mWidth - 1);
	std::uniform_int_distribution<int> yDist(0, mHeight - 1);

	for (int i = 0; i < nMemes; ++i)
	{
		Vec2I spawnPos;
		do
			spawnPos = { xDist(rng), yDist(rng) };
		while (TileAt(spawnPos).HasMeme());

		TileAt(spawnPos).SpawnMeme();
	}
}

void MemeField::Draw(Graphics& gfx) const
{
	gfx.DrawRect(GetRect(), SpriteCodex::baseColor);
	for (Vec2I gridpos = { 0, 0 }; gridpos.Y < mHeight; ++gridpos.Y)
		for (gridpos.X = 0; gridpos.X < mWidth; ++gridpos.X)
			TileAt(gridpos).Draw(gridpos * SpriteCodex::tileSize, gfx);
}

RectI MemeField::GetRect() const
{
	return { 0, mWidth * SpriteCodex::tileSize, 0, mHeight * SpriteCodex::tileSize };
}

void MemeField::OnRevealClick(const Vec2I& screenPos)
{
	const Vec2I gridPos = ScreenToGrid(screenPos);
	assert(gridPos.X >= 0 && gridPos.X < mWidth && gridPos.Y >= 0 && gridPos.Y < mHeight);

	Tile& tile = TileAt(gridPos);
	if (!tile.IsRevealed())
		tile.Reveal();
}

MemeField::Tile& MemeField::TileAt(const Vec2I& gridpos)
{
	return mField[gridpos.Y * mWidth + gridpos.X];
}

const MemeField::Tile& MemeField::TileAt(const Vec2I& gridpos) const
{
	return mField[gridpos.Y * mWidth + gridpos.X];
}

Vec2I MemeField::ScreenToGrid(const Vec2I& screenPos)
{
	return screenPos / SpriteCodex::tileSize;
}

void MemeField::Tile::SpawnMeme()
{
	assert(!mHasMeme);
	mHasMeme = true;
}

bool MemeField::Tile::HasMeme() const
{
	return mHasMeme;
}

void MemeField::Tile::Draw(const Vec2I& screenPos, Graphics& gfx) const
{
	switch (mState)
	{
	case State::Hidden:
		SpriteCodex::DrawTileButton(screenPos, gfx);
		break;
	case State::Flagged:
		SpriteCodex::DrawTileButton(screenPos, gfx);
		SpriteCodex::DrawTileFlag(screenPos, gfx);
		break;
	case State::Revealed:
		if (mHasMeme)
			SpriteCodex::DrawTileBomb(screenPos, gfx);
		else
			SpriteCodex::DrawTile0(screenPos, gfx);
		break;
	}
}

void MemeField::Tile::Reveal()
{
	assert(mState == State::Hidden);
	mState = State::Revealed;
}

bool MemeField::Tile::IsRevealed() const
{
	return mState == State::Revealed;
}
