#pragma once

#include "Vec2I.h"

class Vec2
{
public:
	Vec2() = default;
	Vec2(float x, float y);

	Vec2 operator+(const Vec2& rhs) const;
	Vec2& operator+=(const Vec2& rhs);

	Vec2 operator-(const Vec2& rhs) const;
	Vec2& operator-=(const Vec2& rhs);

	Vec2 operator*(float rhs) const;
	Vec2& operator*=(float rhs);

	float GetLength() const;
	float GetLengthSq() const;

	Vec2& Normalize();
	Vec2 GetNormalized() const;

	explicit operator Vec2I() const;

public:
	float X = 0.0f;
	float Y = 0.0f;
};
