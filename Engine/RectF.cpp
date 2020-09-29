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

bool RectF::IsOverlappingWith(const RectF& other) const
{
	return Right > other.Left && Left < other.Right && Bottom > other.Top && Top < other.Bottom;
}
