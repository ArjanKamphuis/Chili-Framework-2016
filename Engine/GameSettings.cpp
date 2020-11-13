#include "GameSettings.h"

#include <fstream>

GameSettings::GameSettings(const std::string& filename)
{
	std::ifstream fin(filename);
	for (std::string line; std::getline(fin, line);)
	{
		if (line == "[Tile Size]")
			fin >> mTileSize;
		else if (line == "[Board Dimensions]")
			fin >> mBoardWidth >> mBoardHeight;
		else if (line == "[Poison Amount]")
			fin >> mNumPoison;
		else if (line == "[Food Amount]")
			fin >> mNumFood;
		else if (line == "[Speedup Rate]")
			fin >> mSpeedupRate;
		else if (line.empty())
		{ }
		else
			throw std::runtime_error("Bad motherfucking line in settings file: " + line);
	}

	if (mTileSize < 10)
		mTileSize = 10;
	if (mBoardWidth < 5)
		mBoardWidth = 5;
	if (mBoardHeight < 5)
		mBoardHeight = 5;

	const int nTiles = mBoardWidth * mBoardHeight;
	if (mNumFood >= nTiles)
		mNumFood = nTiles / 4;
	if (mNumPoison >= nTiles - mNumFood)
		mNumPoison = nTiles / 3;

	if (mSpeedupRate < 0.5f)
		mSpeedupRate = 0.5f;
	else if (mSpeedupRate > 1.5f)
		mSpeedupRate = 1.5f;
}

int GameSettings::GetTileSize() const
{
	return mTileSize;
}

int GameSettings::GetBoardWidth() const
{
	return mBoardWidth;
}

int GameSettings::GetBoardHeight() const
{
	return mBoardHeight;
}

int GameSettings::GetPoisonAmount() const
{
	return mNumPoison;
}

int GameSettings::GetFoodAmount() const
{
	return mNumFood;
}

float GameSettings::GetSpeedupRate() const
{
	return mSpeedupRate;
}
