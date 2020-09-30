#pragma once

#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF(float left, float right, float top, float bottom);
	RectF(const Vec2& topLeft, const Vec2& bottomRight);
	RectF(const Vec2& topLeft, float width, float height);

	static RectF FromCenter(const Vec2& center, float halfWidth, float halfHeight);

	bool IsOverlappingWith(const RectF& other) const;
	RectF GetExpanded(float offset) const;
	Vec2 GetCenter() const;

public:
	float Left = 0.0f;
	float Right = 0.0f;
	float Top = 0.0f;
	float Bottom = 0.0f;
};

