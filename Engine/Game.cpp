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
#include "ChiliUtil.h"
#include <functional>

#ifdef _DEBUG
#include <crtdbg.h>
#endif

#pragma region overlays
const std::string layer1 =
"AAAAAAAAAADEEAAAAAAAAAAAA"
"AIHIHIHIHICDBIHIHIHIHIHIA"
"AKJKJKJKJKEEDKJKJKJKJKJKA"
"AEEBBFEDEFBCDCCECCCEBDDCA"
"ADCCCCCGBEFEEDEECBCDEEDBA"
"ABBBBBCEBCBCBGBCBDEBDEBCA"
"ABCGFDEEBGEDBCDDEFECBEEBA"
"ADCCCBCCEEEEEBEEGDEGBEDEA"
"ACEECEBCCDEDBBEDDBDBFBDDA"
"ACBCDDFBGFDDEFEDEEDBCCBEA"
"ABBDEEEECECDECFBEDCBEBDBA"
"AEBGEEEFEDCCEECFDCBDDBDDA"
"ACEDDBBCBFDBBCCBEGCCCBEEA"
"ACBBBBEBEGBDDBDCCDECBBBBA"
"AGEDCCEDEDCCCBCEECCDCEDDA"
"AGDDEGCBBCBEEEBCFCDCEGGCA"
"ABEBFBCFBBEDCEDBDGBFBCGBA"
"ADECBCDDCCCDCDDDECECDDDBA"
"AAAAAAAAAAAAAAAAAAAAAAAAA";

const std::string layer2 =
"LLLLLLLLLLAAALLLLLLLLLLLL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LAAAAAAAAAAAAAAAAAAAAAAAL"
"LLLLLLLLLLLLLLLLLLLLLLLLL";
#pragma endregion

Game::Game( MainWindow& wnd )
	: wnd(wnd), gfx(wnd), mBackground1(gfx.GetScreenRectI(), 25, 19, layer1), mBackground2(gfx.GetScreenRectI(), 25, 19, layer2)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	mSndBackground.Play(1.0f, 0.6f);
	std::uniform_real_distribution<float> xd(0, 800);
	std::uniform_real_distribution<float> yd(0, 600);
	for (int i = 0; i < 12; ++i)
		mPoos.emplace_back(Vec2F{ xd(mRng), yd(mRng) });
}

void Game::Go()
{
	//gfx.BeginFrame({ 64, 64, 64 });
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
#ifdef _DEBUG
	const float dt = 1.0f / 60;
#else
	const float dt = mFt.Mark();
#endif

	FrameTimer benchTimer;

	while (!wnd.mouse.IsEmpty())
	{
		const Mouse::Event e = wnd.mouse.Read();
		if (e.GetType() == Mouse::Event::Type::LPress)
		{
			const Vec2F bSpawn = mChili.GetPosition() + Vec2F{ 0.0f, -15.0f };
			Vec2F delta = static_cast<Vec2F>(e.GetPos()) - bSpawn;

			if (delta == Vec2F{})
				delta = { 0.0f, 1.0f };
			else
				delta.Normalize();
						
			mBullets.emplace_back(bSpawn, delta);
		}
	}

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
	mBoundary.Adjust(mChili);

	for (Bullet& b : mBullets)
		b.Update(dt);

	for (Poo& poo : mPoos)
	{
		bool avoiding = false;
		for (const Poo& other : mPoos)
		{
			if (&poo == &other)
				continue;

			const Vec2F delta = poo.GetPosition() - other.GetPosition();
			const float lensq = delta.GetLengthSq();
			if (lensq < 400.0f)
			{
				avoiding = true;
				if (lensq == 0.0f)
					poo.SetDirection({ -1.0f, 1.0f });
				else
					poo.SetDirection(delta / std::sqrt(lensq));
				break;
			}
		}

		if (!avoiding)
		{
			const Vec2F delta = mChili.GetPosition() - poo.GetPosition();
			if (delta.GetLengthSq() > 3.0f)
				poo.SetDirection(delta.GetNormalized());
			else
				poo.SetDirection({});
		}

		poo.Update(dt);
		mBoundary.Adjust(poo);

		if (!poo.IsDead())
		{
			const RectF pooHitbox = poo.GetHitbox();
			if (!mChili.IsInvincible() && mChili.GetHitbox().IsOverlappingWith(pooHitbox))
				mChili.ApplyDamage();

			remove_erase_if(mBullets,
				[&poo, &pooHitbox](const Bullet& b)
				{
					if (b.GetHitbox().IsOverlappingWith(pooHitbox))
					{
						poo.ApplyDamage(35.0f);
						return true;
					}
					return false;
				}
			);
		}
	}

	remove_erase_if(mPoos, std::bind(&Poo::IsReadyForRemoval, std::placeholders::_1));
	remove_erase_if(mBullets,
		[boundRect = mBoundary.GetRect().GetDisplacedBy({ 0.0f, -10.0f })]
		(const Bullet& b)
		{
			return !b.GetHitbox().IsOverlappingWith(boundRect);
		}
	);

	OutputDebugString((std::to_wstring(benchTimer.Mark()) + L'\n').c_str());
}

void Game::ComposeFrame()
{
	mBackground1.Draw(gfx);
	for (const Poo& poo : mPoos)
		poo.Draw(gfx);
	mChili.Draw(gfx);
	for (const Bullet& b : mBullets)
		b.Draw(gfx);
	mBackground2.Draw(gfx);
}
