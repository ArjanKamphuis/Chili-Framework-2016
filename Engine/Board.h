#pragma once

#include <random>
#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	enum class ContentType { Empty, Obstacle, Food, Poison };

public:
	Board(Graphics& gfx);
	Board(const Board& rhs) = delete;
	Board& operator=(const Board& rhs) = delete;
	~Board() = default;

	void DrawCell(const Location& loc, Color c) const;
	void DrawBorder() const;
	void DrawCells() const;

	int GetGridWidth() const;
	int GetGridHeight() const;

	bool IsInsideBoard(const Location& loc) const;

	ContentType GetContent(const Location& loc) const;
	void ConsumeContent(const Location& loc);

	void SpawnContent(std::mt19937& rng, const class Snake& snake, ContentType content);
	void ClearBoard();

private:
	static constexpr Color mBorderColor = Colors::Blue;
	static constexpr Color mObstacleColor = Colors::Gray;
	static constexpr Color mFoodColor = Colors::Red;
	static constexpr Color mPoisonColor = { 64, 8, 64 };
	static constexpr int mDimension = 20;
	static constexpr int mCellPadding = 1;
	static constexpr int mWidth = 32;
	static constexpr int mHeight = 24;
	static constexpr int mBorderWidth = 4;
	static constexpr int mBorderPadding = 2;
	static constexpr int mX = 70;
	static constexpr int mY = 50;

	ContentType mContents[mWidth * mHeight] = {};

	Graphics& mGfx;

	std::uniform_int_distribution<int> mRandomX;
	std::uniform_int_distribution<int> mRandomY;
};

