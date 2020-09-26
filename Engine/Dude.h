#pragma once

#include "GameObject.h"
#include "Keyboard.h"

enum class PlayStyle { Position, Velocity };

class Dude : public GameObject
{
public:
	Dude();
	~Dude() = default;

	void HandleInput(Keyboard& kbd);
	void Draw(Graphics& gfx) const;

private:
	void TogglePlayStyle();

private:
	PlayStyle mPlayStyle = PlayStyle::Position;

	static constexpr float mVelocitySpeed = 1.0f;
	static constexpr float mPositionSpeed = 5.0f;
	float mSpeed = mPositionSpeed;
};

