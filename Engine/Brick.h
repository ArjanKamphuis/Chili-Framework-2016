#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"

class Brick
{
public:
	Brick() = default;
	Brick(const RectF& rect, Color c);

	void Draw(Graphics& gfx) const;

	bool CheckBallCollision(const Ball& ball) const;
	void ExecuteBallCollision(Ball& ball);

	Vec2 GetCenter() const;

private:
	static constexpr float mPadding = 1.0f;
	RectF mRect;
	Color mColor;
	bool mDestroyed = true;
};
