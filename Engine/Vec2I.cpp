#include "Vec2I.h"

#include <cmath>

Vec2I::Vec2I(int x, int y)
	: X(x), Y(y)
{
}

Vec2I Vec2I::operator+(const Vec2I& rhs) const
{
	return Vec2I(X + rhs.X, Y + rhs.Y);
}

Vec2I& Vec2I::operator+=(const Vec2I& rhs)
{
	return *this = *this + rhs;
}

Vec2I Vec2I::operator-(const Vec2I& rhs) const
{
	return Vec2I(X - rhs.X, Y - rhs.Y);
}

Vec2I& Vec2I::operator-=(const Vec2I& rhs)
{
	return *this = *this - rhs;
}

Vec2I Vec2I::operator*(int rhs) const
{
	return Vec2I(X * rhs, Y * rhs);
}

Vec2I& Vec2I::operator*=(int rhs)
{
	return *this = *this * rhs;
}

Vec2I Vec2I::operator/(int rhs) const
{
	return Vec2I(X / rhs, Y /rhs);
}

Vec2I& Vec2I::operator/=(int rhs)
{
	return *this = *this / rhs;
}

int Vec2I::GetLength() const
{
	return static_cast<int>(std::sqrt(GetLengthSq()));
}

int Vec2I::GetLengthSq() const
{
	return X * X + Y * Y;
}
