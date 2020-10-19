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
	mSndTitle.Play();
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
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			mStarted = true;
			mSndMusic.Play(1.0f, 0.6f);
		}
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

	if (mSnekCounter.Tick(dt))
	{
		const Location next = mSnek.GetNextHeadLocation(mDeltaLoc);

		if (!mBrd.IsInsideBoard(next) || mSnek.IsInTile(next, true) || mBrd.CheckForObstacle(next))
		{
			mGameOver = true;
			mSndGameOver.Play();
			mSndMusic.StopAll();
		}
		else
		{
			if (next == mGoal.GetLocation())
			{
				mSnek.GrowAndMoveBy(mDeltaLoc);
				mGoal.Respawn(mRng, mBrd, mSnek);
				mSfxEat.Play(mRng, 0.8f);
			}
			else
				mSnek.MoveBy(mDeltaLoc);
			mSfxSlither.Play(mRng, 0.08f);
		}
	}

	if (mObstacleCounter.Tick(dt))
		mBrd.SpawnObstacle(mRng, mSnek, mGoal);
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
	mSnekCounter.Reset();
	mObstacleCounter.Reset();
	mDeltaLoc = { 1, 0 };

	mBrd.ClearObstacles();
	mSnek.Reset(Location(2, 2));
	mGoal.Respawn(mRng, mBrd, mSnek);
	mGameOver = false;

	mSndMusic.Play(1.0f, 0.6f);
}
