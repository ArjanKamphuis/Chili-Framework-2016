#pragma once

#include "Graphics.h"

class Meter
{
public:
	Meter(int x, int y);
	Meter(const Meter& rhs) = delete;
	Meter& operator=(const Meter& rhs) = delete;
	~Meter() = default;

	void IncreaseLevel();
	void ResetLevel();
	void Draw(Graphics& gfx) const;

private:
	POINT mPosition;
	int mLevel = 0;
	static constexpr Color mColor = Colors::Blue;
	static constexpr int mGirth = 12;
	static constexpr int mScale = 4;

};

