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
	: wnd(wnd),	gfx(wnd), mRng(std::random_device()()), mMeter(20, 20)
{
	mRandoms[L"xDist"] = std::uniform_real_distribution<float>(0.0f, static_cast<float>(gfx.ScreenWidth) - mPoos->GetSize());
	mRandoms[L"yDist"] = std::uniform_real_distribution<float>(0.0f, static_cast<float>(gfx.ScreenHeight) - mPoos->GetSize());
	mRandoms[L"speed"] = std::uniform_real_distribution<float>(-150.0f, 150.0f);

	Restart();
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

	if (mIsStarted)
	{
		if (wnd.kbd.KeyIsPressed('R'))
			Restart();
		
		if (!mIsGameOver)
		{
			mDude.HandleInput(wnd.kbd, dt);
			mDude.Update(dt);

			mGoal.Update();
			if (mGoal.OverlapTest(mDude))
			{
				mMeter.IncreaseLevel();
				mGoal.Respawn(mRandoms[L"xDist"](mRng), mRandoms[L"yDist"](mRng));
				mPickupSound.Play(mRng);
			}

			for (Poo& poo : mPoos)
			{
				poo.Update(dt);
				if (poo.OverlapTest(mDude))
				{
					mIsGameOver = true;
					mFartSound.Play(mRng);
				}
			}
		}
	}
	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			mIsStarted = true;
	}
}

void Game::ComposeFrame()
{
	if (!mIsStarted)
		SpriteCodex::DrawTitle(325, 211, gfx);
	else
	{
		mGoal.Draw(gfx);
		for (const Poo& poo : mPoos)
			poo.Draw(gfx);
		mDude.Draw(gfx);
		mMeter.Draw(gfx);

		if (mIsGameOver)
			SpriteCodex::DrawGameOver(358, 268, gfx);
	}
}

void Game::Restart()
{
	mIsGameOver = false;

	mDude.Respawn(400.0f, 300.0f);
	mGoal.Respawn(mRandoms[L"xDist"](mRng), mRandoms[L"yDist"](mRng));
	mMeter.ResetLevel();

	for (Poo& poo : mPoos)
		poo.Respawn(mRandoms[L"xDist"](mRng), mRandoms[L"yDist"](mRng), mRandoms[L"speed"](mRng), mRandoms[L"speed"](mRng));

	mTitleSound.StopAll();
	mTitleSound.Play();
}
