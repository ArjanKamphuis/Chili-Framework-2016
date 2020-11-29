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
#include "SpriteEffect.h"

Game::Game( MainWindow& wnd )
	: wnd(wnd), gfx(wnd)
{
	mPoos.emplace_back(Vec2F{ 10.0f, 10.0f });
	mPoos.emplace_back(Vec2F{ 700.0f, 10.0f });
	mPoos.emplace_back(Vec2F{ 600.0f, 500.0f });
	mPoos.emplace_back(Vec2F{ 10.0f, 500.0f });
}

void Game::Go()
{
	gfx.BeginFrame({ 64, 64, 64 });
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = mFt.Mark();

	Vec2F dir = {};
	if (wnd.kbd.KeyIsPressed(VK_UP))
		dir.Y -= 1.0f;
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
		dir.Y += 1.0f;
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
		dir.X -= 1.0f;
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		dir.X += 1.0f;

	mChili.SetDirection(dir.GetNormalized());
	mChili.Update(dt);

	for (Poo& poo : mPoos)
	{
		const Vec2F delta = mChili.GetPosition() - poo.GetPosition();
		if (delta.GetLengthSq() > 3.0f)
			poo.SetDirection(delta.GetNormalized());
		else
			poo.SetDirection({});
		poo.Update(dt);

		if (!mChili.IsInvincible() && mChili.GetHitbox().IsOverlappingWith(poo.GetHitbox()))
		{
			mChili.ApplyDamage();
			mSfxHit.Play(mRng);
		}
	}
}

void Game::ComposeFrame()
{
	mFont.DrawText(gfx, "Becky.\nLemme smash.", wnd.mouse.GetPos(), Colors::White);
	for (const Poo& poo : mPoos)
	{
		poo.Draw(gfx);
		gfx.DrawRectThin(static_cast<RectI>(poo.GetHitbox()), Colors::Red);
	}
	mChili.Draw(gfx);
	gfx.DrawRectThin(static_cast<RectI>(mChili.GetHitbox()), Colors::Green);
}
