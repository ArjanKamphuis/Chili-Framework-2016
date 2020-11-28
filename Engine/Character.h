#pragma once

#include "Animation.h"
#include "Vec2.h"

class Character
{
private:
	enum class Sequence { WalkingLeft, WalkingRight, WalkingUp, WalkingDown, StandingLeft, StandingRight, StandingUp, StandingDown, Count };

public:
	Character(const Vec2F& pos);

	void Update(float dt);
	void Draw(Graphics& gfx) const;
	void SetDirection(const Vec2F& dir);

	void ActivateEffect();

private:
	Surface mSprite = "images/link90x90.bmp";
	Vec2F mPosition;
	Vec2F mVelocity = {};
	std::vector<Animation> mAnimations;
	Sequence mCurrSequence = Sequence::StandingDown;
	float mSpeed = 110.0f;

	static constexpr float mEffectDuration = 0.045f;
	float mEffectTime = 0.0f;
	bool mEffectActive = false;
};

