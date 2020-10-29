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
	, mMenu({ gfx.GetScreenRect().GetCenter().X, 200 })
{
}

Game::~Game()
{
	delete mField;
	mField = nullptr;
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
	if (mState == State::SelectionMenu)
		UpdateMenu();
	else
		UpdateGame();
}

void Game::ComposeFrame()
{
	if (mState == State::SelectionMenu)
		mMenu.Draw(gfx);
	else
	{
		mField->Draw(gfx);
		if (mField->GetState() == MemeField::State::Won)
			SpriteCodex::DrawWin(gfx.GetScreenRect().GetCenter(), gfx);
	}
}

void Game::CreateMemeField(int width, int height)
{
	if (mField)
		delete mField;
	mField = new MemeField(gfx.GetScreenRect().GetCenter(), width, height);
}

void Game::UpdateMenu()
{
	while (!wnd.mouse.IsEmpty())
	{
		switch (mMenu.ProcessMouse(wnd.mouse.Read()))
		{
		case SelectionMenu::Size::Small:
			CreateMemeField(8, 4);
			mState = State::MemeSweeper;
			break;
		case SelectionMenu::Size::Medium:
			CreateMemeField(14, 7);
			mState = State::MemeSweeper;
			break;
		case SelectionMenu::Size::Large:
			CreateMemeField(24, 16);
			mState = State::MemeSweeper;
			break;
		}
	}
}

void Game::UpdateGame()
{
	if (mField->GetState() == MemeField::State::Playing && wnd.mouse.LeftIsPressed() && wnd.mouse.RightIsPressed())
	{
		mField->OnClearNeighbors(wnd.mouse.GetPos());
		return;
	}

	while (!wnd.mouse.IsEmpty())
	{
		const Mouse::Event e = wnd.mouse.Read();

		if (mField->GetState() == MemeField::State::Playing)
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
			{
				const Vec2I mousePos = e.GetPos();
				if (mField->GetRect().Contains(mousePos))
					mField->OnRevealClick(mousePos);
			}
			else if (e.GetType() == Mouse::Event::Type::RPress)
			{
				const Vec2I mousePos = e.GetPos();
				if (mField->GetRect().Contains(mousePos))
					mField->OnFlagClick(mousePos);
			}
		}
		else
		{
			if (e.GetType() == Mouse::Event::Type::LPress)
				mState = State::SelectionMenu;
		}
	}
}
