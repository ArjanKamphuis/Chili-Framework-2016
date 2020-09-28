#pragma once

#include <math.h>
#include "Graphics.h"

class GameObject
{
public:
	struct Point
	{
		float X = 0.0f;
		float Y = 0.0f;
	};

public:
	GameObject() = default;
	GameObject(const GameObject& rhs) = delete;
	GameObject& operator=(const GameObject& rhs) = delete;
	virtual ~GameObject() = default;

	virtual void Update(float dt);
	virtual void Draw(Graphics& gfx) const = 0;
	virtual void Respawn(float x, float y, float vx = 0.0f, float vy = 0.0f);
	bool OverlapTest(const GameObject& rhs) const;

	Point GetPosition() const;
	float GetSize() const;

protected:
	GameObject(float size);

protected:
	Point mPosition = {};
	Point mVelocity = {};
	float mSize = 25;
	bool mBouncing = true;
};

