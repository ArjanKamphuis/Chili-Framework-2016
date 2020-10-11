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
	, mBall(Vec2(324.0f, 300.0f), Vec2(-300.0f, -300.0f))
	, mWalls(0.0f, static_cast<float>(Graphics::ScreenWidth), 0.0f, static_cast<float>(Graphics::ScreenHeight))
	, mPaddle(Vec2(400.0f, 500.0f), 50.0f, 15.0f)
{
	const Color colors[4] = { Colors::Red, Colors::Green, Colors::Blue, Colors::Cyan };
	const Vec2 topLeft(40.0f, 40.0f);

	for (int y = 0; y < mNumBricksDown; ++y)
	{
		const Color c = colors[y];
		for (int x = 0; x < mNumBricksAcross; ++x)
			mBricks[(y * mNumBricksAcross) + x] = Brick(RectF(topLeft + Vec2(x * mBrickWidth, y * mBrickHeight), mBrickWidth, mBrickHeight), c);
	}

	mSounds[L"pad"] = Sound(L"Sounds/arkpad.wav");
	mSounds[L"brick"] = Sound(L"Sounds/arkbrick.wav");
	mSounds[L"gameover"] = Sound(L"Sounds/fart.wav");
}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = mFT.Mark();
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	mPaddle.Update(wnd.kbd, dt);
	mPaddle.DoWallCollision(mWalls);
	mBall.Update(dt);

	float colDistSq = FLT_MAX;
	int colIndex = -1;
	for (int i = 0; i < mNumBricks; ++i)
	{
		if (mBricks[i].CheckBallCollision(mBall))
		{
			const float distanceSq = (mBall.GetPosition() - mBricks[i].GetCenter()).GetLengthSq();
			if (distanceSq < colDistSq)
			{
				colDistSq = distanceSq;
				colIndex = i;
			}
		}
	}

	if (colIndex >= 0)
	{
		mPaddle.ResetCooldown();
		mBricks[colIndex].ExecuteBallCollision(mBall);
		mSounds[L"brick"].Play();
	}

	if (mPaddle.DoBallCollision(mBall))
		mSounds[L"pad"].Play();

	if (mBall.DoWallCollision(mWalls))
	{
		mPaddle.ResetCooldown();
		mSounds[L"pad"].Play();
	}
}

void Game::ComposeFrame()
{
	mBall.Draw(gfx);
	for (const Brick& b : mBricks)
		b.Draw(gfx);
	mPaddle.Draw(gfx);
}
