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
	int mSpeed = 5;
};

