#include "Vec2.h"

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

Vec2 Vec2::operator*(float rhs) const
{
	return Vec2(X * rhs, Y * rhs);
}

Vec2& Vec2::operator*=(float rhs)
{
	return *this = *this * rhs;
}
