#pragma once

#include "Graphics.h"
#include "RectF.h"

class Beveler
{
public:
	Beveler(Color base);
	Beveler(const Beveler& rhs) = delete;
	Beveler& operator=(const Beveler& rhs) = delete;
	~Beveler() = default;

	void DrawOuterBevel(const RectF& rect, int size, Graphics& gfx) const;
	void DrawInnerBevel(const RectF& rect, int size, Graphics& gfx) const;
	void DrawBeveledBrick(const RectF& rect, int bevelSize, Graphics& gfx) const;
	void DrawBevelFrame(const RectF& rect, int bevelSize, Graphics& gfx) const;

	Color GetBaseColor() const;
	void SetBaseColor(Color base);

private:
	static constexpr float mLeftFactor = 1.10f;
	static constexpr float mTopFactor = 0.93f;
	static constexpr float mBottomFactor = 0.80f;
	static constexpr float mRightFactor = 0.65f;
	
	Color mBaseColor;
	Color mLeftColor;
	Color mTopColor;
	Color mBottomColor;
	Color mRightColor;
};

