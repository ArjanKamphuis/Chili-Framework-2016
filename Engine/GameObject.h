#pragma once

#include <math.h>
#include "Graphics.h"
#include "Vec2.h"

class GameObject
{
public:
	GameObject() = default;
	GameObject(const GameObject& rhs) = delete;
	GameObject& operator=(const GameObject& rhs) = delete;
	virtual ~GameObject() = default;

	virtual void Update(float dt);
	virtual void Draw(Graphics& gfx) const = 0;
	virtual void Respawn(const Vec2& pos, const Vec2& vel = {});
	bool OverlapTest(const GameObject& rhs) const;

	Vec2 GetPosition() const;
	float GetSize() const;

protected:
	GameObject(float size);

protected:
	Vec2 mPosition = {};
	Vec2 mVelocity = {};
	float mSize = 25;
	bool mBouncing = true;
};

