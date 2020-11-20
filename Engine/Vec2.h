#pragma once

#include <cmath>

template<typename T>
class Vec2
{
public:
	Vec2() = default;
	Vec2(T x, T y)
		: X(x), Y(y)
	{
	}
	template<typename U>
	explicit Vec2(const Vec2<U>& rhs)
		: X(static_cast<T>(rhs.X)), Y(static_cast<T>(rhs.Y))
	{
	}
	Vec2 operator+(const Vec2& rhs) const
	{
		return Vec2(X + rhs.X, Y + rhs.Y);
	}
	Vec2& operator+=(const Vec2& rhs)
	{
		return *this = *this + rhs;
	}
	Vec2 operator-(const Vec2& rhs) const
	{
		return Vec2(X - rhs.X, Y - rhs.Y);
	}
	Vec2& operator-=(const Vec2& rhs)
	{
		return *this = *this - rhs;
	}
	Vec2 operator*(T rhs) const
	{
		return Vec2(X * rhs, Y * rhs);
	}
	Vec2& operator*=(T rhs)
	{
		return *this = *this * rhs;
	}
	T GetLength() const
	{
		return static_cast<T>(std::sqrt(GetLengthSq()));
	}
	T GetLengthSq() const
	{
		return static_cast<T>(X * X + Y * Y);
	}
	Vec2& Normalize()
	{
		return *this = GetNormalized();
	}
	Vec2 GetNormalized() const
	{
		const T len = GetLength();
		return (len != static_cast<T>(0)) ? *this * (static_cast<T>(1) / len) : *this;
	}

public:
	T X = static_cast<T>(0);
	T Y = static_cast<T>(0);
};

using Vec2F = Vec2<float>;
using Vec2I = Vec2<int>;
