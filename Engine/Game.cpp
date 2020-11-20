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
	while (!wnd.kbd.KeyIsEmpty())
	{
		const Keyboard::Event e = wnd.kbd.ReadKey();
		if (e.IsPress() && e.GetCode() == VK_SPACE)
		{
			mLink.ActivateEffect();
			mSndHit.Play();
		}
	}

	Vec2 dir = {};
	if (wnd.kbd.KeyIsDown(VK_UP))
		dir.Y -= 1.0f;
	if (wnd.kbd.KeyIsDown(VK_DOWN))
		dir.Y += 1.0f;
	if (wnd.kbd.KeyIsDown(VK_LEFT))
		dir.X -= 1.0f;
	if (wnd.kbd.KeyIsDown(VK_RIGHT))
		dir.X += 1.0f;

	mLink.SetDirection(dir);
	mLink.Update(mFt.Mark());
}

void Game::ComposeFrame()
{
	mLink.Draw(gfx);
	mFont.DrawText(gfx, "Becky.\nLemme smash.", wnd.mouse.GetPos(), Colors::White);
}
