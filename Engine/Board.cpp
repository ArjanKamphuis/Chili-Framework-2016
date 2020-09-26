#include "Board.h"

Board::Board(Graphics& gfx)
	: mGfx(gfx)
{
}

void Board::DrawCell(const Location& loc, Color c) const
{
	const int x = loc.GetX();
	const int y = loc.GetY();

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
	int x = loc.GetX();
	int y = loc.GetY();

	return x >= 0 && x < mWidth && y >= 0 && y < mHeight;
}
