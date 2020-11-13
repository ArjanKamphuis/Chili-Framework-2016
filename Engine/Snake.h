#pragma once

#include <vector>
#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		Segment(const Location& loc);
		Segment(Color c);

		void Follow(const Segment& next);
		void MoveBy(const Location& delta);
		void Draw(const Board& brd) const;

		const Location& GetLocation() const;

	private:
		Location mLoc = {};
		Color mColor = {};
	};

public:
	Snake(const Location& loc);
	Snake(const Snake& rhs) = delete;
	Snake& operator=(const Snake& rhs) = delete;
	~Snake() = default;

	void MoveBy(const Location& delta);
	void GrowAndMoveBy(const Location& delta);
	void Draw(const Board& brd) const;

	void Reset(const Location& loc);

	bool IsInTile(const Location& tile, bool exceptEnd = false) const;

	Location GetNextHeadLocation(const Location& delta) const;

private:
	static constexpr int mNumBodyColors = 4;
	static constexpr Color mBodyColors[mNumBodyColors] = { { 10, 100, 32 }, { 10, 130, 48 }, { 18, 160, 48 }, { 10, 130, 148 } };
	static constexpr Color mHeadColor = Colors::Yellow;
	std::vector<Segment> mSegments;
};

