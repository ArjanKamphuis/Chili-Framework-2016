#pragma once

#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		Segment() = default;
		Segment(const Segment& rhs) = delete;
		Segment& operator=(const Segment& rhs) = delete;
		~Segment() = default;

		void InitHead(const Location& loc);
		void InitBody(Color c);

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
	void Grow();
	void Draw(const Board& brd) const;

	void Reset(const Location& loc);

	bool IsInTile(const Location& tile, bool exceptEnd = false) const;

	Location GetNextHeadLocation(const Location& delta) const;

private:
	static constexpr Color mHeadColor = Colors::Yellow;
	static constexpr int mMaxSegments = 100;
	Segment mSegments[mMaxSegments] = {};
	int mNumSegments = 1;
};

