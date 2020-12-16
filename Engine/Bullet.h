#pragma once

#include "Animation.h"
#include "SpriteEffect.h"
#include "Codex.h"
#include "Vec2.h"

class Bullet
{
public:
	Bullet(const Vec2F& pos, const Vec2F& dir);

	void Draw(Graphics& gfx) const;
	void Update(float dt);

	const Vec2F& GetPosition() const;
	RectF GetHitbox() const;

private:
	Animation mBulletAnimation = Animation(0, 0, 8, 8, 4, Codex<Surface>::Retreive(L"Images/fireball.bmp"), 0.1f);
	Vec2F mPosition;
	Vec2F mDrawOffset = { -4.0f, -4.0f };
	float mSpeed = 300.0f;
	Vec2F mVelocity;

	float mHitboxHalfWidth = 4.0f;
	float mHitboxHalfHeight = 4.0f;
};

