#include "Beveler.h"

Beveler::Beveler(Color base)
{
	SetBaseColor(base);
}

void Beveler::DrawOuterBevel(const RectF& rect, int size, Graphics& gfx) const
{
	const int left = static_cast<int>(rect.Left);
	const int right = static_cast<int>(rect.Right);
	const int top = static_cast<int>(rect.Top);
	const int bottom = static_cast<int>(rect.Bottom);

	gfx.DrawIsoRightTriBL(left, top, size, mLeftColor);
	gfx.DrawRect(left, top + size, left + size, bottom - size, mLeftColor);
	gfx.DrawIsoRightTriUL(left, bottom - size, size, mLeftColor);

	gfx.DrawIsoRightTriUR(left, top, size, mTopColor);
	gfx.DrawRect(left + size, top, right - size, top + size, mTopColor);
	gfx.DrawIsoRightTriUL(right - size, top, size, mTopColor);

	gfx.DrawIsoRightTriBR(right - size, top, size, mRightColor);
	gfx.DrawRect(right - size, top + size, right, bottom - size, mRightColor);
	gfx.DrawIsoRightTriUR(right - size, bottom - size, size, mRightColor);

	gfx.DrawIsoRightTriBR(left, bottom - size, size, mBottomColor);
	gfx.DrawRect(left + size, bottom - size, right - size, bottom, mBottomColor);
	gfx.DrawIsoRightTriBL(right - size, bottom - size, size, mBottomColor);
}

void Beveler::DrawInnerBevel(const RectF& rect, int size, Graphics& gfx) const
{
	const int left = static_cast<int>(rect.Left);
	const int right = static_cast<int>(rect.Right);
	const int top = static_cast<int>(rect.Top);
	const int bottom = static_cast<int>(rect.Bottom);

	gfx.DrawIsoRightTriBL(left, top, size, mRightColor);
	gfx.DrawRect(left, top + size, left + size, bottom - size, mRightColor);
	gfx.DrawIsoRightTriUL(left, bottom - size, size, mRightColor);

	gfx.DrawIsoRightTriUR(left, top, size, mBottomColor);
	gfx.DrawRect(left + size, top, right - size, top + size, mBottomColor);
	gfx.DrawIsoRightTriUL(right - size, top, size, mBottomColor);

	gfx.DrawIsoRightTriBR(right - size, top, size, mLeftColor);
	gfx.DrawRect(right - size, top + size, right, bottom - size, mLeftColor);
	gfx.DrawIsoRightTriUR(right - size, bottom - size, size, mLeftColor);

	gfx.DrawIsoRightTriBR(left, bottom - size, size, mTopColor);
	gfx.DrawRect(left + size, bottom - size, right - size, bottom, mTopColor);
	gfx.DrawIsoRightTriBL(right - size, bottom - size, size, mTopColor);
}

void Beveler::DrawBeveledBrick(const RectF& rect, int bevelSize, Graphics& gfx) const
{
	DrawOuterBevel(rect, bevelSize, gfx);
	gfx.DrawRect(rect.GetExpanded(-static_cast<float>(bevelSize)), mBaseColor);
}

void Beveler::DrawBevelFrame(const RectF& rect, int bevelSize, Graphics& gfx) const
{
	DrawOuterBevel(rect, bevelSize, gfx);
	DrawInnerBevel(rect.GetExpanded(-static_cast<float>(bevelSize)), bevelSize, gfx);
}

Color Beveler::GetBaseColor() const
{
	return mBaseColor;
}

void Beveler::SetBaseColor(Color base)
{
	mBaseColor = base;
	mTopColor = Color(
		static_cast<int>(static_cast<float>(mBaseColor.GetR()) * mTopFactor),
		static_cast<int>(static_cast<float>(mBaseColor.GetG()) * mTopFactor),
		static_cast<int>(static_cast<float>(mBaseColor.GetB()) * mTopFactor));
	mBottomColor = Color(
		static_cast<int>(static_cast<float>(mBaseColor.GetR()) * mBottomFactor),
		static_cast<int>(static_cast<float>(mBaseColor.GetG()) * mBottomFactor),
		static_cast<int>(static_cast<float>(mBaseColor.GetB()) * mBottomFactor));
	mLeftColor = Color(
		static_cast<int>(static_cast<float>(mBaseColor.GetR()) * mLeftFactor),
		static_cast<int>(static_cast<float>(mBaseColor.GetG()) * mLeftFactor),
		static_cast<int>(static_cast<float>(mBaseColor.GetB()) * mLeftFactor));
	mRightColor = Color(
		static_cast<int>(static_cast<float>(mBaseColor.GetR()) * mRightFactor),
		static_cast<int>(static_cast<float>(mBaseColor.GetG()) * mRightFactor),
		static_cast<int>(static_cast<float>(mBaseColor.GetB()) * mRightFactor));
}
