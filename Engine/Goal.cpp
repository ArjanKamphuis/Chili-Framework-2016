#include "Goal.h"

Goal::Goal(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	mRandoms[L"x"] = std::uniform_int_distribution<int>(0, brd.GetGridWidth() - 1);
	mRandoms[L"y"] = std::uniform_int_distribution<int>(0, brd.GetGridHeight() - 1);

	Respawn(rng, snake, nullptr, 0);
}

void Goal::Respawn(std::mt19937& rng, const Snake& snake, const Obstacle* obstacles, int numObtacles)
{
	bool locationFound = false;
	while (!locationFound)
	{
		mLoc.SetLocation(mRandoms[L"x"](rng), mRandoms[L"y"](rng));
		locationFound = true;

		if (snake.IsInTile(mLoc))
			locationFound = false;

		for (int i = 0; i < numObtacles; ++i)
		{
			if (obstacles[i].GetLocation() == mLoc)
			{
				locationFound = false;
				break;
			}
		}
	}
}

void Goal::Draw(const Board& brd) const
{
	brd.DrawCell(mLoc, mColor);
}

const Location& Goal::GetLocation() const
{
	return mLoc;
}
