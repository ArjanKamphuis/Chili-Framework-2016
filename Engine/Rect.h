#pragma once

#include "Vec2.h"

template<typename T>
class Rect
{
public:
	Rect() = default;
	Rect(T left, T right, T top, T bottom)
		: Left(left), Right(right), Top(top), Bottom(bottom)
	{
	}
	Rect(const Vec2<T> & topLeft, const Vec2<T> & bottomRight)
		: Rect(topLeft.X, bottomRight.X, topLeft.Y, bottomRight.Y)
	{
	}
	Rect(const Vec2<T> & topLeft, int width, int height)
		: Rect(topLeft, topLeft + Vec2<T>(width, height))
	{
	}
	Rect FromCenter(const Vec2<T> & center, int halfWidth, int halfHeight)
	{
		const Vec2<T> half(halfWidth, halfHeight);
		return Rect(center - half, center + half);
	}
	bool IsOverlappingWith(const Rect & other) const
	{
		return Right > other.Left && Left < other.Right&& Bottom > other.Top && Top < other.Bottom;
	}
	bool IsContainedBy(const Rect & other) const
	{
		return Left >= other.Left && Right <= other.Right && Top >= other.Top && Bottom <= other.Bottom;
	}
	bool Contains(const Vec2<T> & point) const
	{
		return point.X >= Left && point.X < Right&& point.Y >= Top && point.Y < Bottom;
	}
	Rect GetExpanded(int offset) const
	{
		return Rect(Left - offset, Right + offset, Top - offset, Bottom + offset);
	}
	Vec2<T> GetCenter() const
	{
		return Vec2<T>((Left + Right) >> 1, (Top + Bottom) >> 1);
	}
	T GetWidth() const
	{
		return Right - Left;
	}
	T GetHeight() const
	{
		return Bottom - Top;
	}

public:
	T Left = static_cast<T>(0);
	T Right = static_cast<T>(0);
	T Top = static_cast<T>(0);
	T Bottom = static_cast<T>(0);
};

using RectF = Rect<float>;
using RectI = Rect<int>;
