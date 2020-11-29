#pragma once

#include "Animation.h"
#include "SpriteEffect.h"
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
	Surface mBullet = "Images/fireball.bmp";
	Animation mBulletAnimation = Animation(0, 0, 8, 8, 4, mBullet, 0.15f);
	Vec2F mPosition;
	Vec2F mDrawOffset = { -4.0f, -4.0f };
	Vec2F mVelocity;
	float mSpeed = 150.0f;

	float mHitboxHalfWidth = 4.0f;
	float mHitboxHalfHeight = 4.0f;
};

