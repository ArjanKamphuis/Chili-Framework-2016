#pragma once

#include "Graphics.h"
#include "Sound.h"

class MemeField
{
public:
	enum class State { Won, Lost, Playing };

private:
	class Tile
	{
	public:
		enum class State { Hidden, Flagged, Revealed};

	public:
		void SpawnMeme();
		bool HasMeme() const;

		void Draw(const Vec2I& screenPos, MemeField::State state, Graphics& gfx) const;

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
	MemeField(const Vec2I& center, int width, int height);
	~MemeField();

	void Draw(Graphics& gfx) const;

	RectI GetRect() const;
	State GetState() const;

	void OnRevealClick(const Vec2I& screenPos);
	void OnFlagClick(const Vec2I& screenPos);
	void OnClearNeighbors(const Vec2I& screenPos);

	void Restart();

private:
	Tile& TileAt(const Vec2I& gridpos);
	const Tile& TileAt(const Vec2I& gridpos) const;
	Vec2I ScreenToGrid(const Vec2I& screenPos) const;

	int CountNeighborMemes(const Vec2I& gridPos) const;

	void RevealTile(const Vec2I& gridPos);
	
	bool GameIsWon() const;

	void SpawnMemes();

private:
	static constexpr int mBorderThickness = 10;
	static constexpr Color mBorderColor = Colors::Blue;

	int mWidth;
	int mHeight;
	int mMemeCount;

	Vec2I mTopLeft;
	State mState = State::Playing;
	Tile* mField = nullptr;

	Sound mSndLose = Sound(L"data/spayed.wav");
};
