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
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "Font.h"

class Game
{
private:
	enum class State { Start, Play, GameOver, Line };
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void UpdateModel();
	void ComposeFrame();
	/********************************/
	/*  User Functions              */
	/********************************/
	int Rotate(int px, int py, int r) const;
	bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY) const;
	Color GetCellColor(int value) const;
	void Restart();
	void DrawTextCenter(const std::string& text, Color c);
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	std::mt19937 mRng = std::mt19937(std::random_device{}());
	std::uniform_int_distribution<int> mDist = std::uniform_int_distribution<int>(0, 6);
	FrameTimer mFt;

	Font mFont = "images/Fixedsys16x28.bmp";

	static constexpr int mFieldWidth = 12;
	static constexpr int mFieldHeight = 18;
	static constexpr int mBlockSize = 25;
	int mOffsetX, mOffsetY, mTextOffset;
	std::vector<int> mField;

	std::wstring mTetrominos[7];

	State mState = State::Start;
	int mCurrentPiece = mDist(mRng);
	int mCurrentRotation = 0;
	int mCurrentX = mFieldWidth / 2 - 2;
	int mCurrentY = 0;

	int mSpeed = 20;
	int mSpeedCount = 0;
	int mPieceCount = 0;
	int mScore = 0;
	bool mForceDown = false;

	std::vector<int> mLines;
	float mLineTimer = 0.0f;
	static constexpr float mLineDisplay = 0.4f;
	/********************************/
};