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
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	: wnd(wnd), gfx(wnd), mRng(std::random_device()())
	, mWalls(RectF::FromCenter(Graphics::GetScreenRect().GetCenter(), mFieldWidth * 0.5f, mFieldHeight * 0.5f), mWallThickness, mWallColor)
	, mPaddle(Vec2(400.0f, 550.0f), 32.0f, 6.0f)
	, mLifeCounter({ 30.0f, 30.0f }, 3)
{
	const Vec2 gridTopLeft(mWalls.GetInnerBounds().Left, mWalls.GetInnerBounds().Top + mTopSpace);
	for (int y = 0; y < mNumBricksDown; ++y)
	{
		const Color c = mBrickColors[y];
		for (int x = 0; x < mNumBricksAcross; ++x)
			mBricks[(y * mNumBricksAcross) + x] = Brick(RectF(gridTopLeft + Vec2(x * mBrickWidth, y * mBrickHeight), mBrickWidth, mBrickHeight), c);
	}

	mSounds[L"pad"] = Sound(L"Sounds/arkpad.wav");
	mSounds[L"brick"] = Sound(L"Sounds/arkbrick.wav");
	mSounds[L"gameover"] = Sound(L"Sounds/fart.wav");
	mSounds[L"getready"] = Sound(L"Sounds/ready.wav");
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
	if (mGameState == GameStates::Playing)
	{
		mPaddle.Update(wnd.kbd, dt);
		mPaddle.DoWallCollision(mWalls.GetInnerBounds());
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

		const int ballWallCollisionResult = mBall.DoWallCollision(mWalls.GetInnerBounds());
		if (ballWallCollisionResult == 1)
		{
			if (!mPaddle.GetRect().IsOverlappingWith(mBall.GetRect()))
				mPaddle.ResetCooldown();
			mSounds[L"pad"].Play();
		}
		else if (ballWallCollisionResult == 2)
		{
			StartRound();
			mSounds[L"gameover"].Play();
		}
	}
	else if (mGameState == GameStates::NotStarted && wnd.kbd.KeyIsPressed(VK_RETURN))
		StartRound();
	else if (mGameState == GameStates::GettingReady && ((mCurrentWaitTime += dt) > mReadyWaitTime))
		mGameState = GameStates::Playing;
}

void Game::ComposeFrame()
{
	if (mGameState == GameStates::Playing || mGameState == GameStates::GettingReady)
	{
		mPaddle.Draw(gfx);
		mLifeCounter.Draw(gfx);
	}
	
	if (mGameState == GameStates::Playing)
		mBall.Draw(gfx);

	if (mGameState != GameStates::NotStarted)
	{
		for (const Brick& b : mBricks)
			b.Draw(gfx);
		mWalls.Draw(gfx);
	}
	
	if (mGameState == GameStates::NotStarted)
		SpriteCodex::DrawTitle(Graphics::GetScreenRect().GetCenter(), gfx);
	else if (mGameState == GameStates::Gameover)
		SpriteCodex::DrawGameOver(Graphics::GetScreenRect().GetCenter(), gfx);
	else if (mGameState == GameStates::GettingReady)
		SpriteCodex::DrawReady(Graphics::GetScreenRect().GetCenter(), gfx);	
}

void Game::StartRound()
{
	if (mLifeCounter.ConsumeLife())
	{
		mCurrentWaitTime = 0.0f;
		mSounds[L"getready"].Play();
		mGameState = GameStates::GettingReady;
		mBall = Ball(Graphics::GetScreenRect().GetCenter(), Vec2(-0.55f, -1.0f));
	}
	else
		mGameState = GameStates::Gameover;
}
