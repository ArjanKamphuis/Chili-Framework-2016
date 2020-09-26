#pragma once

#include <random>
#include "Board.h"
#include "Snake.h"

class Obstacle
{
public:
	Obstacle() = default;
	Obstacle(const Obstacle& rhs) = delete;
	Obstacle& operator=(const Obstacle& rhs) = delete;
	~Obstacle() = default;

	void Spawn(std::mt19937& rng, const Board& brd, const Snake& snake, const Location& goal);
	void Draw(const Board& brd) const;

	const Location& GetLocation() const;

private:
	static constexpr Color mColor = Colors::Gray;
	Location mLoc = {};
};

