#pragma once

#include "Animation.h"
#include "Codex.h"
#include "SoundEffect.h"
#include "SpriteEffect.h"
#include "Vec2.h"

class Chili
{
public:
	class DamageEffectController
	{
	public:
		DamageEffectController(const Chili& parent);

		void Update(float dt);
		void DrawChili(Graphics& gfx) const;
		void Activate();

		bool IsActive() const;

	private:
		const Chili& mParent;
		static constexpr float mRedDuration = 0.045f;
		static constexpr float mTotalDuration = 1.5f;
		static constexpr float mBlinkHalfPeriod = 0.18f;
		float mTime = 0.0f;
		bool mActive = false;
	};

private:
	enum class AnimationSequence { Walking, Standing, Count };

public:
	Chili(const Vec2F& pos);

	void Draw(Graphics& gfx) const;
	void HandleInput(class Keyboard& kbd, class Mouse& mouse, class World& world);
	void Update(World& world, float dt);
	void DisplaceBy(const Vec2F& d);

	void ApplyDamage();
	bool IsInvincible() const;

	const Vec2F& GetPosition() const;
	RectF GetHitbox() const;

private:
	void SetDirection(const Vec2F& dir);
	void ProcessBullet(World& world);

private:
	const Surface* mHeadSurface = Codex<Surface>::Retreive(L"Images/chilihead.bmp");
	const SoundEffect* mSfxHurt = Codex<SoundEffect>::Retreive(L"Sounds/chili_hurt.sfx");

	Vec2F mPosition;
	Vec2F mDrawOffset = { -21.0f, -67.0f };
	Vec2F mVelocity = {};
	std::vector<Animation> mAnimations;
	AnimationSequence mCurrSequence = AnimationSequence::Standing;

	float mHitboxHalfWidth = 10.0f;
	float mHitboxHalfHeight = 9.0f;

	bool mFacingRight = true;
	float mSpeed = 110.0f;

	bool mIsFiring = false;
	Vec2F mBulletDir = {};
	Vec2F mBulletSpawnPos = {};

	DamageEffectController mDamageEffectController = { *this };
};
