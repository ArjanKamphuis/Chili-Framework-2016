#pragma once

#include "Graphics.h"

class Background
{
public:
	Background(const RectI& rect);
	void Draw(Graphics& gfx) const;

private:
	Surface mFloor = "Images/floor.bmp";
	Vec2I mOrigin;
	int mGridWidth;
	int mGridHeight;
};

