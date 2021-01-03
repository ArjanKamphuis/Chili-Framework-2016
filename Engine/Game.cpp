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
	: wnd(wnd), gfx(wnd)
{
	const Vec2I center = gfx.GetScreenRectI().GetCenter();
	mOffsetX = center.X - (mFieldWidth * mBlockSize / 2);
	mOffsetY = center.Y - (mFieldHeight * mBlockSize / 2);
	std::string s = "Score: xxxx";
	mTextOffset = center.X - (mFont.GetGlyphWidth() * s.size() / 2);

	mTetrominos[0].append(L"..X...X...X...X.");
	mTetrominos[1].append(L"..X..XX..X......");
	mTetrominos[2].append(L".X...XX...X.....");
	mTetrominos[3].append(L".....XX..XX.....");
	mTetrominos[4].append(L"..X..XX...X.....");
	mTetrominos[5].append(L".X...X...XX.....");
	mTetrominos[6].append(L"..X...X..XX.....");

	mField.resize(mFieldWidth * mFieldHeight);
	for (size_t y = 0; y < mFieldHeight; y++)
		for (size_t x = 0; x < mFieldWidth; x++)
			mField[y * mFieldWidth + x] = (x == 0 || x == mFieldWidth - 1 || y == mFieldHeight - 1) ? 9 : 0;
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
	const float dt = mFt.Mark();

	switch (mState)
	{
	case State::Start:
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			mState = State::Play;
		break;

	case State::Play:
		while (!wnd.kbd.KeyIsEmpty())
		{
			const Keyboard::Event e = wnd.kbd.ReadKey();
			if (e.IsPress())
			{
				mCurrentX += (e.GetCode() == VK_RIGHT && DoesPieceFit(mCurrentPiece, mCurrentRotation, mCurrentX + 1, mCurrentY)) ? 1 : 0;
				mCurrentX -= (e.GetCode() == VK_LEFT && DoesPieceFit(mCurrentPiece, mCurrentRotation, mCurrentX - 1, mCurrentY)) ? 1 : 0;

				mCurrentRotation += (e.GetCode() == 'Z' && DoesPieceFit(mCurrentPiece, mCurrentRotation + 1, mCurrentX, mCurrentY)) ? 1 : 0;
			}
		}

		if (wnd.kbd.KeyIsPressed(VK_DOWN))
			mCurrentY += DoesPieceFit(mCurrentPiece, mCurrentRotation, mCurrentX, mCurrentY + 1) ? 1 : 0;

		mSpeedCount++;
		mForceDown = (mSpeedCount == mSpeed);

		if (mForceDown)
		{
			mSpeedCount = 0;
			mPieceCount++;
			if (mPieceCount % 50 == 0 && mSpeed >= 10)
				mSpeed--;

			if (DoesPieceFit(mCurrentPiece, mCurrentRotation, mCurrentX, mCurrentY + 1))
				mCurrentY++;
			else
			{
				// Lock the current piece in the field
				for (int py = 0; py < 4; py++)
					for (int px = 0; px < 4; px++)
						if (mTetrominos[mCurrentPiece][Rotate(px, py, mCurrentRotation)] != L'.')
							mField[(mCurrentY + py) * mFieldWidth + (mCurrentX + px)] = mCurrentPiece + 1;

				// Check have we got any lines
				for (int py = 0; py < 4; py++)
				{
					if (mCurrentY + py < mFieldHeight - 1)
					{
						bool bLine = true;
						for (int px = 1; px < mFieldWidth - 1; px++)
							bLine &= (mField[(mCurrentY + py) * mFieldWidth + px]) != 0;

						if (bLine)
						{
							for (int px = 1; px < mFieldWidth - 1; px++)
								mField[(mCurrentY + py) * mFieldWidth + px] = 8;

							mLines.push_back(mCurrentY + py);
							mState = State::Line;
						}
					}
				}

				mScore += 25;
				if (!mLines.empty()) mScore += (1 << mLines.size()) * 100;

				// Choose next piece
				mCurrentX = mFieldWidth / 2 - 2;
				mCurrentY = 0;
				mCurrentRotation = 0;
				mCurrentPiece = mDist(mRng);

				// If piece does not fit
				if (!DoesPieceFit(mCurrentPiece, mCurrentRotation, mCurrentX, mCurrentY))
					mState = State::GameOver;
			}
		}
		break;

	case State::GameOver:
		if (wnd.kbd.KeyIsPressed('R'))
			Restart();
		break;

	case State::Line:
		mLineTimer += dt;
		if (mLineTimer >= mLineDisplay)
		{
			mLineTimer = 0.0f;
			mState = State::Play;

			for (int i : mLines)
			{
				for (int px = 1; px < mFieldWidth - 1; px++)
				{
					for (int py = i; py > 0; py--)
						mField[py * mFieldWidth + px] = mField[(py - 1) * mFieldWidth + px];
					mField[px] = 0;
				}
			}

			mLines.clear();
		}
		break;
	}
}

void Game::ComposeFrame()
{
	// Draw Field
	for (int y = 0; y < mFieldHeight; y++)
		for (int x = 0; x < mFieldWidth; x++)
			gfx.DrawRectDim(mOffsetX + x * mBlockSize + 1, mOffsetY + y * mBlockSize + 1, mBlockSize - 2, mBlockSize - 2, GetCellColor(mField[y * mFieldWidth + x]));

	// Draw Piece
	for (int py = 0; py < 4; py++)
		for (int px = 0; px < 4; px++)
			if (mTetrominos[mCurrentPiece][Rotate(px, py, mCurrentRotation)] == L'X')
				gfx.DrawRectDim(mOffsetX + (mCurrentX + px) * mBlockSize + 1, mOffsetY + (mCurrentY + py) * mBlockSize + 1, mBlockSize - 2, mBlockSize - 2, GetCellColor(mCurrentPiece + 1));

	//// Draw Score
	std::string score = "SCORE: " + std::to_string(mScore);
	mFont.DrawText(gfx, score, { mTextOffset, 10 }, Colors::White);

	if (mState == State::Start)
		DrawTextCenter("Press Enter to begin.", Colors::Green);
	else if (mState == State::GameOver)
		DrawTextCenter("Game Over!! Press R to restart.", Colors::Red);
}

int Game::Rotate(int px, int py, int r) const
{
	switch (r % 4)
	{
	case 0: return py * 4 + px;			// 0 degrees
	case 1: return 12 + py - (px * 4);	// 90 degrees
	case 2: return 15 - (py * 4) - px;	// 180 degrees
	case 3: return 3 - py + (px * 4);	// 270 degrees
	}
	return 0;
}

bool Game::DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY) const
{
	for (int py = 0; py < 4; py++)
	{
		for (int px = 0; px < 4; px++)
		{
			int pi = Rotate(px, py, nRotation);
			int fi = (nPosY + py) * mFieldWidth + (nPosX + px);

			if (nPosY + py >= 0 && nPosY + py < mFieldHeight)
			{
				if (nPosX + px >= 0 && nPosX + px < mFieldWidth)
				{
					if (mTetrominos[nTetromino][pi] == L'X' && mField[fi] != 0)
						return false;
				}
			}
		}
	}

	return true;
}

Color Game::GetCellColor(int value) const
{
	Color c = Colors::Black;
	switch (value)
	{
	case 1: c = Colors::Blue; break;
	case 2: c = Colors::Green; break;
	case 3: c = Colors::Red; break;
	case 4: c = Colors::Magenta; break;
	case 5: c = Colors::Yellow; break;
	case 6: c = Colors::Cyan; break;
	case 7: c = Colors::Gray; break;
	case 8: c = 0xFF9900; break;
	case 9: c = Colors::White; break;
	}
	return c;
}

void Game::Restart()
{
	for (size_t y = 0; y < mFieldHeight; y++)
		for (size_t x = 0; x < mFieldWidth; x++)
			mField[y * mFieldWidth + x] = (x == 0 || x == mFieldWidth - 1 || y == mFieldHeight - 1) ? 9 : 0;

	mLines.clear();

	mState = State::Play;
	mCurrentPiece = mDist(mRng);
	mCurrentRotation = 0;
	mCurrentX = mFieldWidth / 2 - 2;
	mCurrentY = 0;

	mSpeed = 20;
	mSpeedCount = 0;
	mPieceCount = 0;
	mScore = 0;
	mForceDown = false;
}

void Game::DrawTextCenter(const std::string& text, Color c)
{
	const Vec2I p = gfx.GetScreenRectI().GetCenter() - Vec2I{ static_cast<int>(mFont.GetGlyphWidth() * text.size()) / 2, 0 };
	mFont.DrawText(gfx, text, p, c);
}
