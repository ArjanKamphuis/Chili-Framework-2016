#pragma once

#include "Animation.h"
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
	void SetDirection(const Vec2F& dir);
	void Update(float dt);
	void ActivateEffect();

	const Vec2F& GetPosition() const;
	RectF GetHitbox() const;

private:
	Surface mHead = "Images/chilihead.bmp";
	Surface mLegs = "Images/legs-skinny.bmp";
	Vec2F mPosition;
	Vec2F mDrawOffset = { -21.0f, -67.0f };
	Vec2F mVelocity = {};
	std::vector<Animation> mAnimations;
	AnimationSequence mCurrSequence = AnimationSequence::Standing;

	float mHitboxHalfWidth = 10.0f;
	float mHitboxHalfHeight = 9.0f;

	bool mFacingRight = true;
	float mSpeed = 110.0f;

	DamageEffectController mDamageEffectController = { *this };
};
