/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include <random>
#include <unordered_map>
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "Sound.h"
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "Walls.h"
#include "LifeCounter.h"

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void UpdateModel(float dt);
	void ComposeFrame();
	/********************************/
	/*  User Functions              */
	/********************************/
	void StartRound();
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	std::mt19937 mRng;
	FrameTimer mFT;

	static constexpr float mBrickWidth = 40.0f;
	static constexpr float mBrickHeight = 22.0f;
	static constexpr int mNumBricksAcross = 12;
	static constexpr int mNumBricksDown = 4;
	static constexpr int mNumBricks = mNumBricksAcross * mNumBricksDown;
	static constexpr float mTopSpace = mBrickHeight * 1.6f;
	static constexpr float mWallThickness = 12.0f;
	static constexpr float mFieldWidth = static_cast<float>(mNumBricksAcross) * mBrickWidth;
	static constexpr float mFieldHeight = static_cast<float>(Graphics::ScreenHeight) - mWallThickness * 2.0f;
	static constexpr Color mBrickColors[4] = { { 230, 0, 0 }, { 0, 230, 0 }, { 0, 0, 230 }, { 0, 230, 230 } };
	static constexpr Color mWallColor = { 20, 60, 200 };

	Ball mBall;
	Walls mWalls;
	Brick mBricks[mNumBricks];
	Paddle mPaddle;
	LifeCounter mLifeCounter;

	enum class GameStates { NotStarted, GettingReady, Playing, Gameover };
	GameStates mGameState = GameStates::NotStarted;
	static constexpr float mReadyWaitTime = 4.3f;
	float mCurrentWaitTime = 0.0f;

	std::unordered_map<std::wstring, Sound> mSounds;
	/********************************/
};