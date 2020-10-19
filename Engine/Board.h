#pragma once

#include <assert.h>
#include <random>
#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx);
	Board(const Board& rhs) = delete;
	Board& operator=(const Board& rhs) = delete;
	~Board() = default;

	void DrawCell(const Location& loc, Color c) const;
	void DrawBorder() const;
	void DrawObstacles() const;

	int GetGridWidth() const;
	int GetGridHeight() const;

	bool IsInsideBoard(const Location& loc) const;
	bool CheckForObstacle(const Location& loc) const;

	void SpawnObstacle(std::mt19937& rng, const class Snake& snake, const class Goal& goal);
	void ClearObstacles();

private:
	static constexpr Color mBorderColor = Colors::Blue;
	static constexpr Color mObstacleColor = Colors::Gray;
	static constexpr int mDimension = 20;
	static constexpr int mCellPadding = 1;
	static constexpr int mWidth = 32;
	static constexpr int mHeight = 24;
	static constexpr int mBorderWidth = 4;
	static constexpr int mBorderPadding = 2;
	static constexpr int mX = 70;
	static constexpr int mY = 50;

	bool mhasObstacle[mWidth * mHeight] = {};

	Graphics& mGfx;

	std::uniform_int_distribution<int> mRandomX;
	std::uniform_int_distribution<int> mRandomY;
};

