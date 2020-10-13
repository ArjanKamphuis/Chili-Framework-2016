#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"
#include "beveler.h"

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
	static constexpr float mPadding = 0.5f;
	static constexpr int mBevelSize = 3;
	Beveler mBev;
	RectF mRect;
	bool mDestroyed = false;
};
