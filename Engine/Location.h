#pragma once

class Location
{
public:
	Location(int x = 0, int y = 0);

	const Location operator+(const Location& rhs) const;
	Location& operator+=(const Location& rhs);
	bool operator==(const Location& rhs) const;

	void SetLocation(int x, int y);

public:
	int X = 0;
	int Y = 0;
};

