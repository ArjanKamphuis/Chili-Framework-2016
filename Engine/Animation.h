#pragma once

#include <vector>
#include "Graphics.h"
#include "Surface.h"

class Animation
{
public:
	Animation(int x, int y, int width, int height, int count, const Surface& sprite, float holdTime, Color chroma = Colors::Magenta);

	void Draw(Graphics& gfx, const Vec2I& pos) const;
	void Draw(Graphics& gfx, const Vec2I& pos, const RectI& clip) const;
	void DrawColor(Graphics& gfx, const Vec2I& pos, Color c) const;
	void Update(float dt);

private:
	void Advance();

private:
	Color mChroma;
	const Surface& mSprite;
	std::vector<RectI> mFrames;
	int mCurrFrame = 0;
	float mHoldTime;
	float mCurrFrameTime = 0.0f;
};
