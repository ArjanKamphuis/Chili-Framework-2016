#pragma once

#include "Vec2.h"
#include "Graphics.h"

class Ball
{
public:
	Ball(const Vec2& pos, const Vec2& vel);

	void Draw(Graphics& gfx) const;
	void Update(float dt);

	// 0-Nothing, 1-Wall, 2-Bottom
	int DoWallCollision(const RectF& walls);

	void ReboundX();
	void ReboundY();

	RectF GetRect() const;
	Vec2 GetVelocity() const;
	Vec2 GetPosition() const;

private:
	static constexpr float mRadius = 7.0f;
	Vec2 mPosition;
	Vec2 mVelocity;
};

