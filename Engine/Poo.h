#pragma once

#include "GameObject.h"
#include "Dude.h"

class Poo : public GameObject
{
public:
	Poo() = default;
	~Poo() = default;

	void Draw(Graphics& gfx) const;
};
