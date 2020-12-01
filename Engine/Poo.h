#pragma once

#include "SpriteEffect.h"
#include "Vec2.h"

class Poo
{
public:
	Poo(const Vec2F& pos);
	
	void Draw(Graphics& gfx) const;
	void SetDirection(const Vec2F& dir);
	void Update(float dt);

	void ApplyDamage(float damage);
	bool IsDead() const;

	const Vec2F& GetPosition() const;
	RectF GetHitbox() const;

private:
	Surface mPoo = "Images/poo.bmp";
	Vec2F mPosition;
	Vec2F mDrawOffset = { -11.0f, -19.0f };
	Vec2F mVelocity = {};

	float mHitboxHalfWidth = 11.0f;
	float mHitboxHalfHeight = 4.0f;

	float mSpeed = 90.0f;
	static constexpr float mEffectDuration = 0.045f;
	float mEffectTime = 0.0f;
	bool mEffectActive = false;

	int mHp = 100;
};

