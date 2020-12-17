#include "World.h"

#include <functional>

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

World::World(const RectI& screenRect)
	: mBackground1(screenRect, 25, 19, layer1), mBackground2(screenRect, 25, 19, layer2)
{
	mSndBackground.Play(1.0f, 0.6f);
	std::uniform_real_distribution<float> xd(0, 800);
	std::uniform_real_distribution<float> yd(0, 600);
	for (int i = 0; i < 12; ++i)
		mPoos.emplace_back(Vec2F{ xd(mRng), yd(mRng) });
}

void World::HandleInput(Keyboard& kbd, Mouse& mouse)
{
	while (!mouse.IsEmpty())
	{
		const Mouse::Event e = mouse.Read();
		if (e.GetType() == Mouse::Event::Type::LPress)
		{
			const Vec2F bSpawn = mChili.GetPosition() + Vec2F{ 0.0f, -15.0f };
			Vec2F delta = static_cast<Vec2F>(e.GetPos()) - bSpawn;

			if (delta == Vec2F{})
				delta = { 0.0f, 1.0f };
			else
				delta.Normalize();

			SpawnBullet({ bSpawn, delta });
		}
	}

	Vec2F dir = {};
	if (kbd.KeyIsPressed(VK_UP))
		dir.Y -= 1.0f;
	if (kbd.KeyIsPressed(VK_DOWN))
		dir.Y += 1.0f;
	if (kbd.KeyIsPressed(VK_LEFT))
		dir.X -= 1.0f;
	if (kbd.KeyIsPressed(VK_RIGHT))
		dir.X += 1.0f;
	mChili.SetDirection(dir.GetNormalized());

	for (Poo& p : mPoos)
		p.ProcessLogic(*this);
}

void World::Update(float dt)
{
	mChili.Update(dt);
	mBoundary.Adjust(mChili);

	for (Bullet& b : mBullets)
		b.Update(dt);

	for (Poo& poo : mPoos)
	{
		poo.Update(*this, dt);

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

	remove_erase_if(mPoos, std::mem_fn(&Poo::IsReadyForRemoval));
	remove_erase_if(mBullets,
		[boundRect = mBoundary.GetRect().GetDisplacedBy({ 0.0f, -10.0f })]
		(const Bullet& b)
		{
			return !b.GetHitbox().IsOverlappingWith(boundRect);
		}
	);
}

void World::Draw(Graphics& gfx) const
{
	mBackground1.Draw(gfx);
	for (const Poo& poo : mPoos)
		poo.Draw(gfx);
	mChili.Draw(gfx);
	for (const Bullet& b : mBullets)
		b.Draw(gfx);
	mBackground2.Draw(gfx);
}

void World::SpawnBullet(Bullet bullet)
{
	mBullets.emplace_back(bullet);
}

const std::vector<Poo>& World::GetPoos() const
{
	return mPoos;
}

const Chili& World::GetChili() const
{
	return mChili;
}

const std::vector<Bullet>& World::GetBullets() const
{
	return mBullets;
}

const BoundaryF& World::GetBoundary() const
{
	return mBoundary;
}
