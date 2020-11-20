#include "Vec2.h"

#include <cmath>

Vec2::Vec2(float x, float y)
	: X(x), Y(y)
{
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(X + rhs.X, Y + rhs.Y);
}

Vec2& Vec2::operator+=(const Vec2& rhs)
{
	return *this = *this + rhs;
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(X - rhs.X, Y - rhs.Y);
}

Vec2& Vec2::operator-=(const Vec2& rhs)
{
	return *this = *this - rhs;
}

Vec2 Vec2::operator*(float rhs) const
{
	return Vec2(X * rhs, Y * rhs);
}

Vec2& Vec2::operator*=(float rhs)
{
	return *this = *this * rhs;
}

float Vec2::GetLength() const
{
	return std::sqrt(GetLengthSq());
}

float Vec2::GetLengthSq() const
{
	return X * X + Y * Y;
}

Vec2& Vec2::Normalize()
{
	return *this = GetNormalized();
}

Vec2 Vec2::GetNormalized() const
{
	const float len = GetLength();
	return (len != 0.0f) ? *this * (1.0f / len) : *this;
}

Vec2::operator Vec2I() const
{
	return{ static_cast<int>(X), static_cast<int>(Y) };
}
