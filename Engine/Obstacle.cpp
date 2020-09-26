#include "Obstacle.h"

void Obstacle::Spawn(std::mt19937& rng, const Board& brd, const Snake& snake, const Location& goal)
{
	const static std::uniform_int_distribution<int> rX = std::uniform_int_distribution<int>(0, brd.GetGridWidth() - 1);
	const static std::uniform_int_distribution<int> rY = std::uniform_int_distribution<int>(0, brd.GetGridHeight() - 1);

	do
		mLoc.SetLocation(rX(rng), rY(rng));
	while (snake.IsInTile(mLoc) || goal == mLoc);
}

void Obstacle::Draw(const Board& brd) const
{
	brd.DrawCell(mLoc, mColor);
}

const Location& Obstacle::GetLocation() const
{
	return mLoc;
}
