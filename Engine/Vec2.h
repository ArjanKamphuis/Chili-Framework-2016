#pragma once

class Vec2
{
public:
	Vec2() = default;
	Vec2(float x, float y);

	Vec2 operator+(const Vec2& rhs) const;
	Vec2& operator+=(const Vec2& rhs);

	Vec2 operator*(float rhs) const;
	Vec2& operator*=(float rhs);

public:
	float X = 0.0f;
	float Y = 0.0f;
};
