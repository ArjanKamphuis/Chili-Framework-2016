#include "Snake.h"
#include <assert.h>

void Snake::Segment::InitHead(const Location& loc)
{
	mLoc = loc;
	mColor = Snake::mHeadColor;
}

void Snake::Segment::InitBody(Color c)
{
	mColor = c;
}

void Snake::Segment::Follow(const Segment& next)
{
	mLoc = next.mLoc;
}

void Snake::Segment::MoveBy(const Location& delta)
{
	assert(abs(delta.X) + abs(delta.Y) == 1);
	mLoc += delta;
}

void Snake::Segment::Draw(const Board& brd) const
{
	brd.DrawCell(mLoc, mColor);
}

const Location& Snake::Segment::GetLocation() const
{
	return mLoc;
}

Snake::Snake(const Location& loc)
{
	static constexpr int numBodyColors = 4;
	static constexpr Color bodyColors[numBodyColors] = { { 10, 100, 32 }, { 10, 130, 48 }, { 18, 160, 48 }, { 10, 130, 148 } };

	for (int i = 0; i < mMaxSegments; ++i)
		mSegments[i].InitBody(bodyColors[i % numBodyColors]);

	mSegments[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta)
{
	for (int i = mNumSegments - 1; i > 0; --i)
		mSegments[i].Follow(mSegments[i - 1]);
	mSegments[0].MoveBy(delta);
}

void Snake::GrowAndMoveBy(const Location& delta)
{
	if (mNumSegments < mMaxSegments)
		++mNumSegments;
	MoveBy(delta);
}

void Snake::Draw(const Board& brd) const
{
	for (int i = 0; i < mNumSegments; ++i)
		mSegments[i].Draw(brd);
}

void Snake::Reset(const Location& loc)
{
	mNumSegments = 1;
	mSegments[0].InitHead(loc);
}

bool Snake::IsInTile(const Location& tile, bool exceptEnd) const
{
	int snakeLength = exceptEnd ? mNumSegments - 1 : mNumSegments;

	for (int i = 0; i < snakeLength; ++i)
		if (mSegments[i].GetLocation() == tile)
			return true;
	return false;
}

Location Snake::GetNextHeadLocation(const Location& delta) const
{
	return mSegments[0].GetLocation() + delta;
}
