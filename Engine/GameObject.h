#pragma once

#include <math.h>
#include "Graphics.h"

class GameObject
{
public:
	struct Point
	{
		int x = 0;
		int y = 0;
	};

public:
	GameObject() = default;
	GameObject(const GameObject& rhs) = delete;
	GameObject& operator=(const GameObject& rhs) = delete;
	virtual ~GameObject() = default;

	virtual void Update();
	virtual void Draw(Graphics& gfx) const = 0;
	virtual void Respawn(int x, int y, int vx = 0, int vy = 0);
	bool OverlapTest(const GameObject& rhs) const;

	Point GetPosition() const;
	int GetSize() const;

protected:
	GameObject(int size);

protected:
	Point mPosition = {};
	Point mVelocity = {};
	int mSize = 25;
	bool mBouncing = true;
};

