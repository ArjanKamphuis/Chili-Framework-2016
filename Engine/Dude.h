#pragma once

#include "GameObject.h"
#include "Keyboard.h"
#include "Mouse.h"

enum class PlayStyle { Position, Velocity, Mouse };

class Dude : public GameObject
{
public:
	Dude();
	~Dude() = default;

	void HandleInput(Keyboard& kbd, const Mouse& mouse);
	void Draw(Graphics& gfx) const;

private:
	void ChangePlayStyle(PlayStyle style);

private:
	PlayStyle mPlayStyle = PlayStyle::Position;

	static constexpr float mVelocitySpeed = 60.0f;
	static constexpr float mPositionSpeed = 300.0f;
	float mSpeed = mPositionSpeed;
};

