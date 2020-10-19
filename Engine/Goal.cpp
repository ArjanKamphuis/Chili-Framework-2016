#include "Goal.h"

Goal::Goal(std::mt19937& rng, const Board& brd, const Snake& snake)
	: mRandomX(0, brd.GetGridWidth() - 1), mRandomY(0, brd.GetGridHeight() - 1)
{
	Respawn(rng, brd, snake);
}

void Goal::Respawn(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	do
		mLoc.SetLocation(mRandomX(rng), mRandomY(rng));
	while (snake.IsInTile(mLoc) || brd.CheckForObstacle(mLoc));
}

void Goal::Draw(const Board& brd) const
{
	brd.DrawCell(mLoc, mColor);
}

const Location& Goal::GetLocation() const
{
	return mLoc;
}
