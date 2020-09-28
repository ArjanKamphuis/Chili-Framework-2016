#pragma once

#include "GameObject.h"
#include "Keyboard.h"

enum class PlayStyle { Position, Velocity };

class Dude : public GameObject
{
public:
	Dude();
	~Dude() = default;

	void HandleInput(Keyboard& kbd, float dt);
	void Draw(Graphics& gfx) const;

private:
	void TogglePlayStyle();

private:
	PlayStyle mPlayStyle = PlayStyle::Position;

	static constexpr float mVelocitySpeed = 60.0f;
	static constexpr float mPositionSpeed = 300.0f;
	float mSpeed = mPositionSpeed;
};

