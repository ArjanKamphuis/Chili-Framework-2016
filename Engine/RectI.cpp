#include "RectI.h"

RectI::RectI(int left, int right, int top, int bottom)
	: Left(left), Right(right), Top(top), Bottom(bottom)
{
}

RectI::RectI(const Vec2I& topLeft, const Vec2I& bottomRight)
	: RectI(topLeft.X, bottomRight.X, topLeft.Y, bottomRight.Y)
{
}

RectI::RectI(const Vec2I& topLeft, int width, int height)
	: RectI(topLeft, topLeft + Vec2I(width, height))
{
}

RectI RectI::FromCenter(const Vec2I& center, int halfWidth, int halfHeight)
{
	const Vec2I half(halfWidth, halfHeight);
	return RectI(center - half, center + half);
}

bool RectI::IsOverlappingWith(const RectI& other) const
{
	return Right > other.Left && Left < other.Right && Bottom > other.Top && Top < other.Bottom;
}

bool RectI::IsContainedBy(const RectI& other) const
{
	return Left >= other.Left && Right <= other.Right && Top >= other.Top && Bottom <= other.Bottom;
}

RectI RectI::GetExpanded(int offset) const
{
	return RectI(Left - offset, Right + offset, Top - offset, Bottom + offset);
}

Vec2I RectI::GetCenter() const
{
	return Vec2I((Left + Right) >> 1, (Top + Bottom) >> 1);
}
