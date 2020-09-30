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
	static constexpr float mWingWidth = 18.0f;
	Color mWingColor = Colors::Red;
	Color mColor = Colors::White;
	float mSpeed = 300.0f;
	float mHalfWidth;
	float mHalfHeight;
	Vec2 mPosition;
	bool mIsOnCooldown = false;
};

