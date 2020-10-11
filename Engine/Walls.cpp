#include "Walls.h"
#include <cassert>

Walls::Walls(const RectF& innerBounds, float thickness, Color baseColor)
	: mInnerBounds(innerBounds), mThickness(thickness), mBev(baseColor)
{
	assert(static_cast<int>(thickness) % 2 == 0);
	assert(innerBounds.GetExpanded(thickness).IsContainedBy(Graphics::GetScreenRect()));
}

const RectF& Walls::GetInnerBounds() const
{
	return mInnerBounds;
}

void Walls::Draw(Graphics& gfx) const
{
	mBev.DrawBevelFrame(mInnerBounds.GetExpanded(mThickness), static_cast<int>(mThickness) / 2, gfx);
}
