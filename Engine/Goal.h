#pragma once

#include <random>
#include <unordered_map>
#include "Board.h"
#include "Snake.h"
#include "Obstacle.h"

class Goal
{
public:
	Goal(std::mt19937& rng, const Board& brd, const Snake& snake);
	Goal(const Goal& rhs) = delete;
	Goal& operator=(const Goal& rhs) = delete;
	~Goal() = default;

	void Respawn(std::mt19937& rng, const Snake& snake, const Obstacle* obstacles, int numObtacles);
	void Draw(const Board& brd) const;

	const Location& GetLocation() const;

private:
	static constexpr Color mColor = Colors::Red;
	Location mLoc = {};

	std::unordered_map<std::wstring, std::uniform_int_distribution<int>> mRandoms;
};

