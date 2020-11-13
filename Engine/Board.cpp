#include "Board.h"

#include <assert.h>
#include "Snake.h"

Board::Board(Graphics& gfx, const GameSettings& settings)
	: mGfx(gfx), mDimension(settings.GetTileSize()), mWidth(settings.GetBoardWidth()), mHeight(settings.GetBoardHeight())
	, mContents(new ContentType[mWidth * mHeight]{ ContentType::Empty })
	, mRandomX(0, mWidth - 1), mRandomY(0, mHeight - 1)
	, mX(static_cast<int>(gfx.GetScreenRect().GetCenter().X) - (mWidth * mDimension / 2))
	, mY(static_cast<int>(gfx.GetScreenRect().GetCenter().Y) - (mHeight * mDimension / 2))
{
}

Board::~Board()
{
	delete[] mContents;
	mContents = nullptr;
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

void Board::DrawCells() const
{
	for (int y = 0; y < mHeight; ++y)
	{
		for (int x = 0; x < mWidth; ++x)
		{
			switch (mContents[y * mWidth + x])
			{
			case ContentType::Food:
				DrawCell({ x, y }, mFoodColor);
				break;
			case ContentType::Obstacle:
				DrawCell({ x, y }, mObstacleColor);
				break;
			case ContentType::Poison:
				DrawCell({ x, y }, mPoisonColor);
				break;
			}
		}
	}
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

Board::ContentType Board::GetContent(const Location& loc) const
{
	return mContents[loc.Y * mWidth + loc.X];
}

void Board::ConsumeContent(const Location& loc)
{
	const ContentType content = GetContent(loc);
	assert(content == ContentType::Food || content == ContentType::Poison);
	mContents[loc.Y * mWidth + loc.X] = ContentType::Empty;
}

void Board::SpawnContent(std::mt19937& rng, const Snake& snake, ContentType content)
{
	Location newLoc;
	do
	{
		newLoc.X = mRandomX(rng);
		newLoc.Y = mRandomY(rng);
	} while (snake.IsInTile(newLoc) || GetContent(newLoc) != ContentType::Empty);

	mContents[newLoc.Y * mWidth + newLoc.X] = content;
}

void Board::ClearBoard()
{
	for (int y = 0; y < mHeight; ++y)
		for (int x = 0; x < mWidth; ++x)
			mContents[y * mWidth + x] = ContentType::Empty;
}
