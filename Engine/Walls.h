#pragma once

#include "RectF.h"
#include "Beveler.h"
#include "Graphics.h"

class Walls
{
public:
	Walls(const RectF& innerBounds, float thickness, Color baseColor);
	Walls(const Walls& rhs) = delete;
	Walls& operator=(const Walls& rhs) = delete;
	~Walls() = default;

	const RectF& GetInnerBounds() const;
	void Draw(Graphics& gfx) const;

private:
	RectF mInnerBounds;
	float mThickness;
	Beveler mBev;
};

