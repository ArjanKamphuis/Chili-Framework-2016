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
#include "Board.h"
#include "Snake.h"
#include "Goal.h"
#include "SoundEffect.h"
#include "ObjectCounter.h"

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
	/********************************/
	void Restart();
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	std::mt19937 mRng;
	FrameTimer mFT;
	
	Board mBrd;
	Snake mSnek;
	Goal mGoal;
	Location mDeltaLoc = { 1, 0 };

	ObjectCounter mSnekCounter = ObjectCounter(0.06f, 0.4f, 0.005f, 0.15f);

	bool mStarted = false;
	bool mGameOver = false;

	SoundEffect mSfxEat = SoundEffect({ L"data/eat.wav" });
	SoundEffect mSfxSlither = SoundEffect({ L"data/slither0.wav", L"data/slither1.wav", L"data/slither2.wav" });
	Sound mSndMusic = Sound(L"data/music_loop.wav", Sound::LoopType::AutoFullSound);
	Sound mSndTitle = Sound(L"data/title.wav");
	Sound mSndGameOver = Sound(L"data/fart.wav");
	/********************************/
};