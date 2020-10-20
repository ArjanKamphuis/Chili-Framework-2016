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

	for (Vec2I gridPos = { 0, 0 }; gridPos.Y < mHeight; ++gridPos.Y)
		for (gridPos.X = 0; gridPos.X < mWidth; ++gridPos.X)
			TileAt(gridPos).SetNeighborMemeCount(CountNeighborMemes(gridPos));
}

void MemeField::Draw(Graphics& gfx) const
{
	gfx.DrawRect(GetRect(), SpriteCodex::baseColor);
	for (Vec2I gridPos = { 0, 0 }; gridPos.Y < mHeight; ++gridPos.Y)
		for (gridPos.X = 0; gridPos.X < mWidth; ++gridPos.X)
			TileAt(gridPos).Draw(gridPos * SpriteCodex::tileSize, mGameOver, gfx);
}

RectI MemeField::GetRect() const
{
	return { 0, mWidth * SpriteCodex::tileSize, 0, mHeight * SpriteCodex::tileSize };
}

void MemeField::OnRevealClick(const Vec2I& screenPos)
{
	if (!mGameOver)
	{
		const Vec2I gridPos = ScreenToGrid(screenPos);
		assert(gridPos.X >= 0 && gridPos.X < mWidth&& gridPos.Y >= 0 && gridPos.Y < mHeight);

		Tile& tile = TileAt(gridPos);
		if (!tile.IsRevealed() && !tile.IsFlagged())
		{
			tile.Reveal();
			if (tile.HasMeme())
				mGameOver = true;
		}
	}
}

void MemeField::OnFlagClick(const Vec2I& screenPos)
{
	if (!mGameOver)
	{
		const Vec2I gridPos = ScreenToGrid(screenPos);
		assert(gridPos.X >= 0 && gridPos.X < mWidth&& gridPos.Y >= 0 && gridPos.Y < mHeight);

		Tile& tile = TileAt(gridPos);
		if (!tile.IsRevealed())
			tile.ToggleFlag();
	}
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

int MemeField::CountNeighborMemes(const Vec2I& gridPos) const
{
	const int xStart = std::max(0, gridPos.X - 1);
	const int yStart = std::max(0, gridPos.Y - 1);
	const int xEnd = std::min(mWidth - 1, gridPos.X + 1);
	const int yEnd = std::min(mHeight - 1, gridPos.Y + 1);

	int count = 0;
	for (Vec2I gridPos = { xStart, yStart }; gridPos.Y <= yEnd; ++gridPos.Y)
		for (gridPos.X = xStart; gridPos.X <= xEnd; ++gridPos.X)
			if (TileAt(gridPos).HasMeme())
				++count;
	return count;
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

void MemeField::Tile::Draw(const Vec2I& screenPos, bool gameover, Graphics& gfx) const
{
	if (gameover)
	{
		switch (mState)
		{
		case State::Hidden:
			if (mHasMeme)
				SpriteCodex::DrawTileBomb(screenPos, gfx);
			else
				SpriteCodex::DrawTileButton(screenPos, gfx);
			break;
		case State::Flagged:
			if (mHasMeme)
			{
				SpriteCodex::DrawTileBomb(screenPos, gfx);
				SpriteCodex::DrawTileFlag(screenPos, gfx);
			}
			else
			{
				SpriteCodex::DrawTileBomb(screenPos, gfx);
				SpriteCodex::DrawTileCross(screenPos, gfx);
			}
			break;
		case State::Revealed:
			if (mHasMeme)
				SpriteCodex::DrawTileBombRed(screenPos, gfx);
			else
				SpriteCodex::DrawTileNumber(screenPos, mNumNeighborMemes, gfx);
			break;
		}
	}
	else
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
				SpriteCodex::DrawTileNumber(screenPos, mNumNeighborMemes, gfx);
			break;
		}
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

void MemeField::Tile::ToggleFlag()
{
	assert(!IsRevealed());
	mState = mState == State::Hidden ? State::Flagged : State::Hidden;
}

bool MemeField::Tile::IsFlagged() const
{
	return mState == State::Flagged;
}

void MemeField::Tile::SetNeighborMemeCount(int memeCount)
{
	assert(mNumNeighborMemes == -1);
	mNumNeighborMemes = memeCount;
}
