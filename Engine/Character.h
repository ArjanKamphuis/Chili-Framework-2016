#pragma once

#include "Animation.h"
#include "Vec2.h"

class Character
{
private:
	enum class Sequence { WalkingLeft, WalkingRight, WalkingUp, WalkingDown, StandingLeft, StandingRight, StandingUp, StandingDown, Count };

public:
	Character(const Vec2& pos);

	void Update(float dt);
	void Draw(Graphics& gfx) const;
	void SetDirection(const Vec2& dir);

	void ActivateEffect();

private:
	Surface mSprite = "images/link90x90.bmp";
	Vec2 mPosition;
	Vec2 mVelocity = {};
	std::vector<Animation> mAnimations;
	Sequence mCurrSequence = Sequence::StandingDown;
	float mSpeed = 110.0f;

	static constexpr float mEffectDuration = 0.045f;
	float mEffectTime = 0.0f;
	bool mEffectActive = false;
};
