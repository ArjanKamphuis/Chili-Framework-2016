#pragma once

#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF(float left, float right, float top, float bottom);
	RectF(const Vec2F& topLeft, const Vec2F& bottomRight);
	RectF(const Vec2F& topLeft, float width, float height);

	static RectF FromCenter(const Vec2F& center, float halfWidth, float halfHeight);

	bool IsOverlappingWith(const RectF& other) const;
	bool IsContainedBy(const RectF& other) const;

	RectF GetExpanded(float offset) const;
	Vec2F GetCenter() const;

public:
	float Left = 0.0f;
	float Right = 0.0f;
	float Top = 0.0f;
	float Bottom = 0.0f;
};

