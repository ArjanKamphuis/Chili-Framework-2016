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
	: wnd(wnd), gfx(wnd), mRng(std::random_device()()), mBrd(gfx, mSettings), mSnek({ 2, 2 })
	, mNumFood(mSettings.GetFoodAmount()), mNumPoison(mSettings.GetPoisonAmount())
	, mSnekCounter(0.04f, 0.4f, mSettings.GetSpeedupRate(), 0.15f)
{
	FillBoard();
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

	if (mSnekCounter.Tick(dt, wnd.kbd.KeyIsDown(VK_CONTROL)))
	{
		const Location next = mSnek.GetNextHeadLocation(mDeltaLoc);
		const Board::ContentType content = mBrd.IsInsideBoard(next) ? mBrd.GetContent(next) : Board::ContentType::Empty;

		if (!mBrd.IsInsideBoard(next) || mSnek.IsInTile(next, true) || content == Board::ContentType::Obstacle)
		{
			mGameOver = true;
			mSfxFart.Play(mRng, 1.2f);
			mSndMusic.StopAll();
		}
		else
		{
			switch (content)
			{
			case Board::ContentType::Food:
				mSnek.GrowAndMoveBy(mDeltaLoc);
				mBrd.ConsumeContent(next);
				mBrd.SpawnContent(mRng, mSnek, Board::ContentType::Food);
				mBrd.SpawnContent(mRng, mSnek, Board::ContentType::Obstacle);
				mSfxEat.Play(mRng, 0.8f);
				break;
			case Board::ContentType::Poison:
				mSnek.MoveBy(mDeltaLoc);
				mBrd.ConsumeContent(next);
				mBrd.SpawnContent(mRng, mSnek, Board::ContentType::Poison);
				mSnekCounter.Speedup();
				mSfxFart.Play(mRng, 0.6f);
				break;
			case Board::ContentType::Empty:
				mSnek.MoveBy(mDeltaLoc);
				mSfxSlither.Play(mRng, 0.08f);
				break;
			}				
		}
	}
}

void Game::ComposeFrame()
{
	if (mStarted)
	{
		mSnek.Draw(mBrd);
		mBrd.DrawBorder();
		mBrd.DrawCells();

		if (mGameOver)
			SpriteCodex::DrawGameOver(350, 265, gfx);
	}
	else
		SpriteCodex::DrawTitle(290, 225, gfx);

}

void Game::Restart()
{
	mSnekCounter.Reset();
	mSnek.Reset(Location(2, 2));
	mDeltaLoc = { 1, 0 };

	mBrd.ClearBoard();
	FillBoard();

	mGameOver = false;
	mSndMusic.Play(1.0f, 0.6f);
}

void Game::FillBoard()
{
	for (int i = 0; i < mNumFood; ++i)
		mBrd.SpawnContent(mRng, mSnek, Board::ContentType::Food);
	for (int i = 0; i < mNumPoison; ++i)
		mBrd.SpawnContent(mRng, mSnek, Board::ContentType::Poison);
}
