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
	: wnd(wnd), gfx(wnd), mRng(std::random_device()())
{
}

void Game::Go()
{
	gfx.BeginFrame({ 32, 32, 32 });
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = mFt.Mark();
	a.Update(dt);
}

void Game::ComposeFrame()
{
	const Vec2I facepos = wnd.mouse.GetPos();
	const Vec2I legspos = facepos + Vec2I{ 7, 40 };
	const bool mirrored = wnd.kbd.KeyIsPressed(VK_SPACE);

	a.Draw(gfx, legspos, mirrored);
	gfx.DrawSprite(facepos.X, facepos.Y, s, SpriteEffect::Chroma{ Colors::Magenta }, mirrored);
}
