#include "Location.h"

Location::Location(int x, int y)
	: mX(x), mY(y)
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
	mX += rhs.mX;
	mY += rhs.mY;
	return *this;
}

bool Location::operator==(const Location& rhs) const
{
	return mX == rhs.mX && mY == rhs.mY;
}

void Location::SetLocation(int x, int y)
{
	mX = x;
	mY = y;
}

int Location::GetX() const
{
	return mX;
}

int Location::GetY() const
{
	return mY;
}
