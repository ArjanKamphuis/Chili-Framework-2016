#pragma once

#include "Vec2.h"
#include "Graphics.h"

class Ball
{
public:
	Ball(const Vec2& pos, const Vec2& vel);

	void Draw(Graphics& gfx);
	void Update(float dt);

	bool DoWallCollision(const RectF& walls);
	void ReboundX();
	void ReboundY();

	RectF GetRect() const;

private:
	static constexpr float mRadius = 7.0f;
	Vec2 mPosition;
	Vec2 mVelocity;
};

