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
	void ActivateEffect();

	const Vec2F& GetPosition() const;

private:
	Surface mPoo = "Images/poo.bmp";
	Vec2F mPosition;
	Vec2F mVelocity = {};

	float mSpeed = 90.0f;
	static constexpr float mEffectDuration = 0.045f;
	float mEffectTime = 0.0f;
	bool mEffectActive = false;
};

