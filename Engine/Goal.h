#pragma once

#include "GameObject.h"
#include "Dude.h"

class Goal : public GameObject
{
public:
	Goal();
	~Goal() = default;

	void Update(float dt) override;
	void Draw(Graphics& gfx) const;

private:
	int mR = 127;
	int mGB = 0;
	bool mColorIncrease = true;
	static constexpr int mColorSpeed = 2;
};

