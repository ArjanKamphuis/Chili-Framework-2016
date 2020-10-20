#pragma once

#include "Graphics.h"

class MemeField
{
private:
	class Tile
	{
	public:
		enum class State { Hidden, Flagged, Revealed};

	public:
		void SpawnMeme();
		bool HasMeme() const;

		void Draw(const Vec2I& screenPos, bool gameover, Graphics& gfx) const;

		void Reveal();
		bool IsRevealed() const;

		void ToggleFlag();
		bool IsFlagged() const;

		void SetNeighborMemeCount(int memeCount);
		int GetNeighborMemeCount() const;

	private:
		State mState = State::Hidden;
		bool mHasMeme = false;
		int mNumNeighborMemes = -1;
	};

public:
	MemeField(int nMemes);

	void Draw(Graphics& gfx) const;
	RectI GetRect() const;

	void OnRevealClick(const Vec2I& screenPos);
	void OnFlagClick(const Vec2I& screenPos);

private:
	Tile& TileAt(const Vec2I& gridpos);
	const Tile& TileAt(const Vec2I& gridpos) const;
	Vec2I ScreenToGrid(const Vec2I& screenPos);

	int CountNeighborMemes(const Vec2I& gridPos) const;

	void OnEmptyTileClick(const Vec2I& gridPos);

private:
	static constexpr int mWidth = 20;
	static constexpr int mHeight = 16;
	bool mGameOver = false;
	Tile mField[mWidth * mHeight] = {};
};
