#include "Vec2.h"

Vec2::Vec2(float x, float y)
	: mX(x), mY(y)
{
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(mX + rhs.mX, mY + rhs.mY);
}

Vec2& Vec2::operator+=(const Vec2& rhs)
{
	return *this = *this + rhs;
}

Vec2 Vec2::operator*(float rhs) const
{
	return Vec2(mX * rhs, mY * rhs);
}

Vec2& Vec2::operator*=(float rhs)
{
	return *this = *this * rhs;
}
