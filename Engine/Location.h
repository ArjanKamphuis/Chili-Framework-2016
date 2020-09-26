#pragma once

class Location
{
public:
	Location(int x = 0, int y = 0);

	const Location operator+(const Location& rhs) const;
	Location& operator+=(const Location& rhs);
	bool operator==(const Location& rhs) const;

	void SetLocation(int x, int y);

	int GetX() const;
	int GetY() const;

private:
	int mX = 0;
	int mY = 0;
};

