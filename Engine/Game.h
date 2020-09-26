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
#include "Poo.h"
#include "Dude.h"
#include "Goal.h"
#include "Meter.h"
#include "SoundEffect.h"

class Game
{
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
	void Restart();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	std::mt19937 mRng;
	std::unordered_map<std::wstring, std::uniform_int_distribution<int>> mRandoms;

	bool mIsStarted = false;
	bool mIsGameOver = false;
	Dude mDude = {};
	Meter mMeter;
	static constexpr int mNumPoos = 25;
	Poo mPoos[mNumPoos] = {};
	Goal mGoal = {};

	SoundEffect mPickupSound = SoundEffect({ L"Sounds/coin.wav" });
	Sound mTitleSound = Sound({ L"Sounds/title.wav" });
	SoundEffect mFartSound = SoundEffect({ L"Sounds/fart1.wav", L"Sounds/fart2.wav" });
	/********************************/
};