#pragma once

#include "Graphics.h"

class SpriteCodex
{
public:
	SpriteCodex() = delete;
	SpriteCodex(const SpriteCodex& rhs) = delete;
	SpriteCodex& operator=(const SpriteCodex& rhs) = delete;
	~SpriteCodex() = delete;

	static void DrawGameOver(int x, int y, Graphics& gfx);
	static void DrawTitle(int x, int y, Graphics& gfx);
};
