#pragma once

#include <random>
#include <vector>
#include "Background.h"
#include "Boundary.h"
#include "Bullet.h"
#include "Chili.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Poo.h"
#include "Sound.h"

class World
{
public:
	World(const RectI& screenRect);
	
	void HandleInput(Keyboard& kbd, Mouse& mouse);
	void Update(float dt);
	void Draw(Graphics& gfx) const;
	
	void SpawnBullet(Bullet bullet);

private:
	std::mt19937 mRng = std::mt19937(std::random_device{}());

	Sound mSndBackground = Sound(L"Sounds/come.mp3", Sound::LoopType::AutoFullSound);

	Background mBackground1;
	Background mBackground2;
	Chili mChili = Vec2F{ 300.0f, 300.0f };
	std::vector<Poo> mPoos;
	std::vector<Bullet> mBullets;

	BoundaryF mBoundary = RectF{ 32.0f, 768.0f, 96.0f, 576.0f + 64.0f };
};

