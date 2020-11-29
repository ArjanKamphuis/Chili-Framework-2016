#pragma once

#include "Animation.h"
#include "SpriteEffect.h"
#include "Vec2.h"

class Chili
{
private:
	enum class Sequence { Walking, Standing, Count };

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
	Vec2F mDrawOffset = { -20.0f, -67.0f };
	Vec2F mVelocity = {};
	std::vector<Animation> mAnimations;
	Sequence mCurrSequence = Sequence::Standing;

	float mHitboxHalfWidth = 10.0f;
	float mHitboxHalfHeight = 9.0f;

	bool mFacingRight = true;
	float mSpeed = 110.0f;
	static constexpr float mEffectDuration = 0.045f;
	float mEffectTime = 0.0f;
	bool mEffectActive = false;
};
