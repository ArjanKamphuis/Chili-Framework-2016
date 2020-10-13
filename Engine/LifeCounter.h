#pragma once

#include "Graphics.h"
#include "Vec2.h"

class LifeCounter
{
public:
	LifeCounter(Vec2 pos, int lives);

	bool ConsumeLife();
	void Draw(Graphics& gfx) const;

private:
	static constexpr float mSpacing = 28.0f;
	int mLives;
	Vec2 mPos;
};

