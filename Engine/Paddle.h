#pragma once

#include "Ball.h"
#include "Vec2.h"
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Keyboard.h"

class Paddle
{
public:
	Paddle(const Vec2& pos, float halfWidth, float halfHeight);

	void Draw(Graphics& gfx) const;
	void Update(Keyboard& kbd, float dt);

	bool DoBallCollision(Ball& ball);
	void DoWallCollision(const RectF& walls);
	void ResetCooldown();

	RectF GetRect() const;

private:
	static constexpr Color mWingColor = { 210, 255, 210 };
	static constexpr Color mColor = { 200, 220, 200 };
	static constexpr float mWingWidth = 6.0f;
	static constexpr float mSpeed = 360.0f;
	static constexpr float mMaxmimumExitRatio = 2.6f;
	static constexpr float mFixedZoneWidthRatio = 0.2f;

	float mHalfWidth;
	float mHalfHeight;

	float mExitXFactor;
	float mFixedZoneHalfWidth;
	float mFixedZoneExitX;

	Vec2 mPosition;
	bool mIsOnCooldown = false;
};

