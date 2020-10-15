#include "Location.h"

Location::Location(int x, int y)
	: X(x), Y(y)
{
}

const Location Location::operator+(const Location& rhs) const
{
	Location ret = *this;
	ret += rhs;
	return ret;
}

Location& Location::operator+=(const Location& rhs)
{
	X += rhs.X;
	Y += rhs.Y;
	return *this;
}

bool Location::operator==(const Location& rhs) const
{
	return X == rhs.X && Y == rhs.Y;
}

void Location::SetLocation(int x, int y)
{
	X = x;
	Y = y;
}
