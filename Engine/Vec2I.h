#pragma once

class Vec2I
{
public:
	Vec2I() = default;
	Vec2I(int x, int y);

	Vec2I operator+(const Vec2I& rhs) const;
	Vec2I& operator+=(const Vec2I& rhs);

	Vec2I operator-(const Vec2I& rhs) const;
	Vec2I& operator-=(const Vec2I& rhs);

	Vec2I operator*(int rhs) const;
	Vec2I& operator*=(int rhs);

	Vec2I operator/(int rhs) const;
	Vec2I& operator/=(int rhs);

	int GetLength() const;
	int GetLengthSq() const;

public:
	int X = 0;
	int Y = 0;
};
