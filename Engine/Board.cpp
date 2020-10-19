#include "Board.h"

#include "Snake.h"
#include "Goal.h"

Board::Board(Graphics& gfx)
	: mGfx(gfx), mRandomX(0, mWidth - 1), mRandomY(0, mHeight - 1)
{
}

void Board::DrawCell(const Location& loc, Color c) const
{
	const int x = loc.X;
	const int y = loc.Y;

	assert(x >= 0.0f);
	assert(x < mWidth);
	assert(y >= 0.0f);
	assert(y < mHeight);

	const int offsetX = mX + mBorderWidth + mBorderPadding;
	const int offsetY = mY + mBorderWidth + mBorderPadding;

	mGfx.DrawRectDim(x * mDimension + offsetX + mCellPadding, y * mDimension + offsetY + mCellPadding, mDimension - 2 * mCellPadding, mDimension - 2 * mCellPadding, c);
}

void Board::DrawBorder() const
{
	const int left = mX;
	const int top = mY;
	const int right = left + (mBorderWidth + mBorderPadding) * 2 + mWidth * mDimension;
	const int bottom = top + (mBorderWidth + mBorderPadding) * 2 + mHeight * mDimension;

	mGfx.DrawRect(left, top, right, top + mBorderWidth, mBorderColor);
	mGfx.DrawRect(left, top + mBorderWidth, left + mBorderWidth, bottom - mBorderWidth, mBorderColor);
	mGfx.DrawRect(right - mBorderWidth, top + mBorderWidth, right, bottom - mBorderWidth, mBorderColor);
	mGfx.DrawRect(left, bottom - mBorderWidth, right, bottom, mBorderColor);
}

void Board::DrawObstacles() const
{
	for (int y = 0; y < mHeight; ++y)
		for (int x = 0; x < mWidth; ++x)
			if (CheckForObstacle({ x, y }))
				DrawCell({ x, y }, mObstacleColor);
}

int Board::GetGridWidth() const
{
	return mWidth;
}

int Board::GetGridHeight() const
{
	return mHeight;
}

bool Board::IsInsideBoard(const Location& loc) const
{
	int x = loc.X;
	int y = loc.Y;

	return x >= 0 && x < mWidth && y >= 0 && y < mHeight;
}

bool Board::CheckForObstacle(const Location& loc) const
{
	return mhasObstacle[loc.Y * mWidth + loc.X];
}

void Board::SpawnObstacle(std::mt19937& rng, const Snake& snake, const Goal& goal)
{
	Location newLoc;
	do
	{
		newLoc.X = mRandomX(rng);
		newLoc.Y = mRandomY(rng);
	} while (snake.IsInTile(newLoc)|| CheckForObstacle(newLoc) || goal.GetLocation() == newLoc);

	mhasObstacle[newLoc.Y * mWidth + newLoc.X] = true;
}

void Board::ClearObstacles()
{
	for (int y = 0; y < mHeight; ++y)
		for (int x = 0; x < mWidth; ++x)
			mhasObstacle[y * mWidth + x] = false;
}
