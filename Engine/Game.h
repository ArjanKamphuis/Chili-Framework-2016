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
#include "SoundEffect.h"
#include "Chili.h"
#include "Poo.h"
#include "Bullet.h"
#include "Background.h"
#include "Boundary.h"

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
	void RemoveDeadObjects();
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	std::mt19937 mRng = std::mt19937(std::random_device{}());
	FrameTimer mFt;

	Font mFont = L"Images/Fixedsys16x28.bmp";
	Sound mSndBallHit = L"Sounds/fhit.wav";
	Sound mSndBallLaunch = L"Sounds/fball.wav";
	Sound mSndDeath = L"Sounds/monster_death.wav";
	Sound mSndBackground = Sound(L"Sounds/come.mp3", Sound::LoopType::AutoFullSound);

	Background mBackground1;
	Background mBackground2;
	Chili mChili = Vec2F{ 300.0f, 300.0f };
	std::vector<Poo> mPoos;
	std::vector<Bullet> mBullets;

	BoundaryF mBoundary = RectF{ 32.0f, 768.0f, 96.0f, 576.0f + 64.0f };
	/********************************/
};