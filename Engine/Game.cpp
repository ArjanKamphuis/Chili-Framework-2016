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

	++mSnekMoveCounter;
	if (mSnekMoveCounter >= mSnekMovePeriod)
	{
		mSnekMoveCounter = 0;
		const Location next = mSnek.GetNextHeadLocation(mDeltaLoc);

		for (int i = 0; i < mNumObstacles; ++i)
		{
			if (mObstacles[i].GetLocation() == next)
			{
				mGameOver = true;
				return;
			}
		}

		if (!mBrd.IsInsideBoard(next) || mSnek.IsInTile(next, true))
			mGameOver = true;
		else
		{
			const bool eating = next == mGoal.GetLocation();
			if (eating)
				mSnek.Grow();
			mSnek.MoveBy(mDeltaLoc);
			if (eating)
				mGoal.Respawn(mRng, mSnek, mObstacles, mNumObstacles);
		}
	}

	++mSnekSpeedupCounter;
	if (mSnekSpeedupCounter >= mSnekSpeedupPeriod)
	{
		mSnekSpeedupCounter = 0;
		mSnekMovePeriod = std::max(mSnekMovePeriod - 1, mSnekMovePeriodMin);

		mObstacles[mNumObstacles++].Spawn(mRng, mBrd, mSnek, mGoal.GetLocation());
	}
}

void Game::ComposeFrame()
{
	if (mStarted)
	{
		mSnek.Draw(mBrd);
		mGoal.Draw(mBrd);

		for (int i = 0; i < mNumObstacles; ++i)
			mObstacles[i].Draw(mBrd);

		if (mGameOver)
			SpriteCodex::DrawGameOver(350, 265, gfx);

		mBrd.DrawBorder();
	}
	else
		SpriteCodex::DrawTitle(290, 225, gfx);

}

void Game::Restart()
{
	mNumObstacles = 0;
	mSnekMovePeriod = 20;
	mSnekMoveCounter = 0;
	mSnekSpeedupCounter = 0;
	mDeltaLoc = { 1, 0 };

	mSnek.Reset(Location(2, 2));
	mGoal.Respawn(mRng, mSnek, mObstacles, mNumObstacles);
	mGameOver = false;
}
