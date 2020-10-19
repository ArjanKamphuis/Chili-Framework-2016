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
	: wnd(wnd), gfx(wnd), mRng(std::random_device()()), mBrd(gfx), mSnek(Location(2, 2)), mGoal(mRng, mBrd, mSnek)
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

	if (!mStarted)
	{
		mStarted = wnd.kbd.KeyIsPressed(VK_RETURN);
		return;
	}

	if (mGameOver)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			Restart();
		return;
	}

	if (wnd.kbd.KeyIsPressed(VK_LEFT))
		mDeltaLoc.SetLocation(-1, 0);
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		mDeltaLoc.SetLocation(1, 0);
	if (wnd.kbd.KeyIsPressed(VK_UP))
		mDeltaLoc.SetLocation(0, -1);
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
		mDeltaLoc.SetLocation(0, 1);

	mSnekMoveCounter += dt;
	if (mSnekMoveCounter >= mSnekMovePeriod)
	{
		mSnekMoveCounter -= mSnekMovePeriod;
		const Location next = mSnek.GetNextHeadLocation(mDeltaLoc);

		if (!mBrd.IsInsideBoard(next) || mSnek.IsInTile(next, true) || mBrd.CheckForObstacle(next))
			mGameOver = true;
		else
		{
			if (next == mGoal.GetLocation())
			{
				mSnek.GrowAndMoveBy(mDeltaLoc);
				mGoal.Respawn(mRng, mBrd, mSnek);
			}
			else
				mSnek.MoveBy(mDeltaLoc);
		}
	}

	mObstacleSpawnCounter += dt;
	if (mObstacleSpawnCounter >= mObstacleSpawnPeriod)
	{
		mObstacleSpawnCounter -= mObstacleSpawnPeriod;
		mBrd.SpawnObstacle(mRng, mSnek, mGoal);
	}

	mSnekMovePeriod = std::max(mSnekMovePeriod - dt * mSnekSpeedupFactor, mSnekMovePeriodMin);
	mObstacleSpawnPeriod = std::max(mObstacleSpawnPeriod - dt * mObstacleSpawnSpeedupFactor, mObstacleSpawnPeriodMin);
}

void Game::ComposeFrame()
{
	if (mStarted)
	{
		mSnek.Draw(mBrd);
		mGoal.Draw(mBrd);

		if (mGameOver)
			SpriteCodex::DrawGameOver(350, 265, gfx);

		mBrd.DrawBorder();
		mBrd.DrawObstacles();
	}
	else
		SpriteCodex::DrawTitle(290, 225, gfx);

}

void Game::Restart()
{
	mSnekMovePeriod = mSnekMovePeriodStart;
	mSnekMoveCounter = 0.0f;
	mObstacleSpawnPeriod = mObstacleSpawnPeriodStart;
	mObstacleSpawnCounter = 0.0f;
	mDeltaLoc = { 1, 0 };

	mBrd.ClearObstacles();
	mSnek.Reset(Location(2, 2));
	mGoal.Respawn(mRng, mBrd, mSnek);
	mGameOver = false;
}
