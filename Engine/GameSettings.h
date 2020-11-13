#pragma once

#include <string>

class GameSettings
{
public:
	GameSettings(const std::string& filename);

	int GetTileSize() const;
	int GetBoardWidth() const;
	int GetBoardHeight() const;
	int GetPoisonAmount() const;
	int GetFoodAmount() const;
	float GetSpeedupRate() const;

private:
	int mTileSize = 0;
	int mBoardWidth = 0;
	int mBoardHeight = 0;
	int mNumPoison = 0;
	int mNumFood = 0;
	float mSpeedupRate = 0.0f;
};

