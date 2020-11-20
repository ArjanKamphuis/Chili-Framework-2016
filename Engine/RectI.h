#pragma once

#include "Vec2.h"

class RectI
{
public:
	RectI() = default;
	RectI(int left, int right, int top, int bottom);
	RectI(const Vec2I& topLeft, const Vec2I& bottomRight);
	RectI(const Vec2I& topLeft, int width, int height);

	static RectI FromCenter(const Vec2I& center, int halfWidth, int halfHeight);

	bool IsOverlappingWith(const RectI& other) const;
	bool IsContainedBy(const RectI& other) const;
	bool Contains(const Vec2I& point) const;

	RectI GetExpanded(int offset) const;
	Vec2I GetCenter() const;
	int GetWidth() const;
	int GetHeight() const;

public:
	int Left = 0;
	int Right = 0;
	int Top = 0;
	int Bottom = 0;
};

