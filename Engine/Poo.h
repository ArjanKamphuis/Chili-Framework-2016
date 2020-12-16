#pragma once

#include "Codex.h"
#include "Sound.h"
#include "SpriteEffect.h"
#include "Vec2.h"

class Poo
{
private:
	enum class EffectState { Normal, Hit, Dying };

public:
	Poo(const Vec2F& pos);
	
	void Draw(Graphics& gfx) const;
	void SetDirection(const Vec2F& dir);
	void Update(float dt);
	void DisplaceBy(const Vec2F& d);

	void ApplyDamage(float damage);
	bool IsDead() const;
	bool IsReadyForRemoval() const;

	const Vec2F& GetPosition() const;
	RectF GetHitbox() const;

private:
	const Surface* mPooSurface = Codex<Surface>::Retreive(L"Images/poo.bmp");
	const Sound* mSndHit = Codex<Sound>::Retreive(L"Sounds/fhit.wav");
	const Sound* mSndDeath = Codex<Sound>::Retreive(L"Sounds/monster_death.wav");

	Vec2F mPosition;
	Vec2F mDrawOffset = { -11.0f, -19.0f };
	Vec2F mVelocity = {};

	float mHitboxHalfWidth = 11.0f;
	float mHitboxHalfHeight = 4.0f;

	float mSpeed = 90.0f;
	static constexpr float mDissolveDuration = 0.6f;
	static constexpr float mHitFlashDuration = 0.045f;
	float mEffectTime = 0.0f;
	EffectState mEffectState = EffectState::Normal;
	bool mIsReadyForRemoval = false;

	int mHp = 100;
};

