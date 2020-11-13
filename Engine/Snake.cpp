#include "Snake.h"
#include <assert.h>

Snake::Segment::Segment(const Location& loc)
{
	mLoc = loc;
	mColor = Snake::mHeadColor;
}

Snake::Segment::Segment(Color c)
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
	mSegments.emplace_back(loc);
}

void Snake::MoveBy(const Location& delta)
{
	for (size_t i = mSegments.size() - 1; i > 0; --i)
		mSegments[i].Follow(mSegments[i - 1]);
	mSegments.front().MoveBy(delta);
}

void Snake::GrowAndMoveBy(const Location& delta)
{
	mSegments.emplace_back(mBodyColors[mSegments.size() % mNumBodyColors]);
	MoveBy(delta);
}

void Snake::Draw(const Board& brd) const
{
	for (const Segment& s : mSegments)
		s.Draw(brd);
}

void Snake::Reset(const Location& loc)
{
	mSegments.clear();
	mSegments.emplace_back(loc);
}

bool Snake::IsInTile(const Location& tile, bool exceptEnd) const
{
	size_t snakeLength = exceptEnd ? mSegments.size() - 1 : mSegments.size();

	for (size_t i = 0; i < snakeLength; ++i)
		if (mSegments[i].GetLocation() == tile)
			return true;
	return false;
}

Location Snake::GetNextHeadLocation(const Location& delta) const
{
	return mSegments.front().GetLocation() + delta;
}
