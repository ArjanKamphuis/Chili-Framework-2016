#pragma once

#include <random>
#include "Board.h"
#include "Snake.h"

class Goal
{
public:
	Goal(std::mt19937& rng, const Board& brd, const Snake& snake);
	Goal(const Goal& rhs) = delete;
	Goal& operator=(const Goal& rhs) = delete;
	~Goal() = default;

	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snake);
	void Draw(const Board& brd) const;

	const Location& GetLocation() const;

private:
	static constexpr Color mColor = Colors::Red;
	Location mLoc = {};

	std::uniform_int_distribution<int> mRandomX;
	std::uniform_int_distribution<int> mRandomY;
};

