#include "RectF.h"

RectF::RectF(float left, float right, float top, float bottom)
	: Left(left), Right(right), Top(top), Bottom(bottom)
{
}

RectF::RectF(const Vec2F& topLeft, const Vec2F& bottomRight)
	: RectF(topLeft.X, bottomRight.X, topLeft.Y, bottomRight.Y)
{
}

RectF::RectF(const Vec2F& topLeft, float width, float height)
	: RectF(topLeft, topLeft + Vec2F(width, height))
{
}

RectF RectF::FromCenter(const Vec2F& center, float halfWidth, float halfHeight)
{
	const Vec2F half(halfWidth, halfHeight);
	return RectF(center - half, center + half);
}

bool RectF::IsOverlappingWith(const RectF& other) const
{
	return Right > other.Left && Left < other.Right && Bottom > other.Top && Top < other.Bottom;
}

bool RectF::IsContainedBy(const RectF& other) const
{
	return Left >= other.Left && Right <= other.Right && Top >= other.Top && Bottom <= other.Bottom;
}

RectF RectF::GetExpanded(float offset) const
{
	return RectF(Left - offset, Right + offset, Top - offset, Bottom + offset);
}

Vec2F RectF::GetCenter() const
{
	return Vec2F(0.5f * (Left + Right), 0.5f * (Top + Bottom));
}
