#pragma once

#include <random>
#include <vector>
#include "Graphics.h"
#include "Location.h"
#include "GameSettings.h"

class Board
{
public:
	enum class ContentType { Empty, Obstacle, Food, Poison };

public:
	Board(Graphics& gfx, const GameSettings& settings);

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
	static constexpr int mCellPadding = 1;
	static constexpr int mBorderWidth = 4;
	static constexpr int mBorderPadding = 2;

	int mWidth;
	int mHeight;
	int mDimension;
	int mX;
	int mY;

	std::vector<ContentType> mContents;

	Graphics& mGfx;

	std::uniform_int_distribution<int> mRandomX;
	std::uniform_int_distribution<int> mRandomY;
};

