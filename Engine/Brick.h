#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"

class Brick
{
public:
	Brick(const RectF& rect, Color c);

	void Draw(Graphics& gfx);

	bool DoBallCollision(Ball& ball);

private:
	RectF mRect;
	Color mColor;
	bool mDestroyed = false;
};
