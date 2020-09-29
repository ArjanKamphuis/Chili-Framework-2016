/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	: wnd(wnd), gfx(wnd), mRng(std::random_device()())
	, mBall(Vec2(300.0f, 300.0f), Vec2(300.0f, 300.0f))
	, mWalls(0.0f, static_cast<float>(Graphics::ScreenWidth), 0.0f, static_cast<float>(Graphics::ScreenHeight))
	, mBrick(RectF(450.0f, 550.0f, 485.0f, 515.0f), Colors::Red)
	, mSoundPad(L"Sounds/arkpad.wav")
	, mSoundBrick(L"Sounds/arkbrick.wav")
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = mFT.Mark();
	mBall.Update(dt);

	if (mBrick.DoBallCollision(mBall))
	{
		mSoundBrick.Play();
	}

	if (mBall.DoWallCollision(mWalls))
		mSoundPad.Play();
}

void Game::ComposeFrame()
{
	mBall.Draw(gfx);
	mBrick.Draw(gfx);
}
