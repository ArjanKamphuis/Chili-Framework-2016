#include "RectF.h"

RectF::RectF(float left, float right, float top, float bottom)
	: Left(left), Right(right), Top(top), Bottom(bottom)
{
}

RectF::RectF(const Vec2& topLeft, const Vec2& bottomRight)
	: RectF(topLeft.X, bottomRight.X, topLeft.Y, bottomRight.Y)
{
}

RectF::RectF(const Vec2& topLeft, float width, float height)
	: RectF(topLeft, topLeft + Vec2(width, height))
{
}

RectF RectF::FromCenter(const Vec2& center, float halfWidth, float halfHeight)
{
	const Vec2 half(halfWidth, halfHeight);
	return RectF(center - half, center + half);
}

bool RectF::IsOverlappingWith(const RectF& other) const
{
	return Right > other.Left && Left < other.Right && Bottom > other.Top && Top < other.Bottom;
}
