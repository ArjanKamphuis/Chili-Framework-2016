#include "Dude.h"

Dude::Dude()
	: GameObject(20)
{
}

void Dude::HandleInput(Keyboard& kbd)
{
	if (kbd.KeyIsPressed('Z'))
		TogglePlayStyle();

	if (mPlayStyle == PlayStyle::Position)
	{
		if (kbd.KeyIsDown(VK_LEFT))
			mPosition.x -= mSpeed;
		if (kbd.KeyIsDown(VK_RIGHT))
			mPosition.x += mSpeed;
		if (kbd.KeyIsDown(VK_UP))
			mPosition.y -= mSpeed;
		if (kbd.KeyIsDown(VK_DOWN))
			mPosition.y += mSpeed;
	}
	else
	{
		if (kbd.KeyIsPressed(VK_LEFT))
			mVelocity.x -= mSpeed;
		if (kbd.KeyIsPressed(VK_RIGHT))
			mVelocity.x += mSpeed;
		if (kbd.KeyIsPressed(VK_UP))
			mVelocity.y -= mSpeed;
		if (kbd.KeyIsPressed(VK_DOWN))
			mVelocity.y += mSpeed;
	}
}

void Dude::Draw(Graphics& gfx) const
{
	gfx.PutPixel(7 + mPosition.x, 0 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(8 + mPosition.x, 0 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(9 + mPosition.x, 0 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(10 + mPosition.x, 0 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(11 + mPosition.x, 0 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(12 + mPosition.x, 0 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(5 + mPosition.x, 1 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(6 + mPosition.x, 1 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(7 + mPosition.x, 1 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(8 + mPosition.x, 1 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(9 + mPosition.x, 1 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(10 + mPosition.x, 1 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(11 + mPosition.x, 1 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(12 + mPosition.x, 1 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(13 + mPosition.x, 1 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(14 + mPosition.x, 1 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(3 + mPosition.x, 2 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(4 + mPosition.x, 2 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(5 + mPosition.x, 2 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(6 + mPosition.x, 2 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(7 + mPosition.x, 2 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(8 + mPosition.x, 2 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(9 + mPosition.x, 2 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(10 + mPosition.x, 2 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(11 + mPosition.x, 2 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(12 + mPosition.x, 2 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(13 + mPosition.x, 2 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(14 + mPosition.x, 2 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(15 + mPosition.x, 2 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(16 + mPosition.x, 2 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(2 + mPosition.x, 3 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(3 + mPosition.x, 3 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(4 + mPosition.x, 3 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(5 + mPosition.x, 3 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(6 + mPosition.x, 3 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(7 + mPosition.x, 3 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(8 + mPosition.x, 3 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(9 + mPosition.x, 3 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(10 + mPosition.x, 3 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(11 + mPosition.x, 3 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(12 + mPosition.x, 3 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(13 + mPosition.x, 3 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(14 + mPosition.x, 3 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(15 + mPosition.x, 3 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(16 + mPosition.x, 3 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(17 + mPosition.x, 3 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(2 + mPosition.x, 4 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(3 + mPosition.x, 4 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(4 + mPosition.x, 4 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(5 + mPosition.x, 4 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(6 + mPosition.x, 4 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(7 + mPosition.x, 4 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(8 + mPosition.x, 4 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(9 + mPosition.x, 4 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(10 + mPosition.x, 4 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(11 + mPosition.x, 4 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(12 + mPosition.x, 4 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(13 + mPosition.x, 4 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(14 + mPosition.x, 4 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(15 + mPosition.x, 4 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(16 + mPosition.x, 4 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(17 + mPosition.x, 4 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(1 + mPosition.x, 5 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(2 + mPosition.x, 5 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(3 + mPosition.x, 5 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(4 + mPosition.x, 5 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(5 + mPosition.x, 5 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(6 + mPosition.x, 5 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(7 + mPosition.x, 5 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(8 + mPosition.x, 5 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(9 + mPosition.x, 5 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(10 + mPosition.x, 5 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(11 + mPosition.x, 5 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(12 + mPosition.x, 5 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(13 + mPosition.x, 5 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(14 + mPosition.x, 5 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(15 + mPosition.x, 5 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(16 + mPosition.x, 5 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(17 + mPosition.x, 5 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(18 + mPosition.x, 5 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(1 + mPosition.x, 6 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(2 + mPosition.x, 6 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(3 + mPosition.x, 6 + mPosition.y, 255, 255, 255);
	gfx.PutPixel(4 + mPosition.x, 6 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(5 + mPosition.x, 6 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(6 + mPosition.x, 6 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(7 + mPosition.x, 6 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(8 + mPosition.x, 6 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(9 + mPosition.x, 6 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(10 + mPosition.x, 6 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(11 + mPosition.x, 6 + mPosition.y, 255, 255, 255);
	gfx.PutPixel(12 + mPosition.x, 6 + mPosition.y, 255, 255, 255);
	gfx.PutPixel(13 + mPosition.x, 6 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(14 + mPosition.x, 6 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(15 + mPosition.x, 6 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(16 + mPosition.x, 6 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(17 + mPosition.x, 6 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(18 + mPosition.x, 6 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(0 + mPosition.x, 7 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(1 + mPosition.x, 7 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(2 + mPosition.x, 7 + mPosition.y, 255, 255, 255);
	gfx.PutPixel(3 + mPosition.x, 7 + mPosition.y, 255, 255, 255);
	gfx.PutPixel(4 + mPosition.x, 7 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(5 + mPosition.x, 7 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(6 + mPosition.x, 7 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(7 + mPosition.x, 7 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(8 + mPosition.x, 7 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(9 + mPosition.x, 7 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(10 + mPosition.x, 7 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(11 + mPosition.x, 7 + mPosition.y, 255, 255, 255);
	gfx.PutPixel(12 + mPosition.x, 7 + mPosition.y, 255, 255, 255);
	gfx.PutPixel(13 + mPosition.x, 7 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(14 + mPosition.x, 7 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(15 + mPosition.x, 7 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(16 + mPosition.x, 7 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(17 + mPosition.x, 7 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(18 + mPosition.x, 7 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(19 + mPosition.x, 7 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(0 + mPosition.x, 8 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(1 + mPosition.x, 8 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(2 + mPosition.x, 8 + mPosition.y, 255, 255, 255);
	gfx.PutPixel(3 + mPosition.x, 8 + mPosition.y, 255, 255, 255);
	gfx.PutPixel(4 + mPosition.x, 8 + mPosition.y, 255, 255, 255);
	gfx.PutPixel(5 + mPosition.x, 8 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(6 + mPosition.x, 8 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(7 + mPosition.x, 8 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(8 + mPosition.x, 8 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(9 + mPosition.x, 8 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(10 + mPosition.x, 8 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(11 + mPosition.x, 8 + mPosition.y, 255, 255, 255);
	gfx.PutPixel(12 + mPosition.x, 8 + mPosition.y, 255, 255, 255);
	gfx.PutPixel(13 + mPosition.x, 8 + mPosition.y, 255, 255, 255);
	gfx.PutPixel(14 + mPosition.x, 8 + mPosition.y, 255, 255, 255);
	gfx.PutPixel(15 + mPosition.x, 8 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(16 + mPosition.x, 8 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(17 + mPosition.x, 8 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(18 + mPosition.x, 8 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(19 + mPosition.x, 8 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(0 + mPosition.x, 9 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(1 + mPosition.x, 9 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(2 + mPosition.x, 9 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(3 + mPosition.x, 9 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(4 + mPosition.x, 9 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(5 + mPosition.x, 9 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(6 + mPosition.x, 9 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(7 + mPosition.x, 9 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(8 + mPosition.x, 9 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(9 + mPosition.x, 9 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(10 + mPosition.x, 9 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(11 + mPosition.x, 9 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(12 + mPosition.x, 9 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(13 + mPosition.x, 9 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(14 + mPosition.x, 9 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(15 + mPosition.x, 9 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(16 + mPosition.x, 9 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(17 + mPosition.x, 9 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(18 + mPosition.x, 9 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(19 + mPosition.x, 9 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(0 + mPosition.x, 10 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(1 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(2 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(3 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(4 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(5 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(6 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(7 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(8 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(9 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(10 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(11 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(12 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(13 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(14 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(15 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(16 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(17 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(18 + mPosition.x, 10 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(19 + mPosition.x, 10 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(0 + mPosition.x, 11 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(1 + mPosition.x, 11 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(2 + mPosition.x, 11 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(3 + mPosition.x, 11 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(4 + mPosition.x, 11 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(5 + mPosition.x, 11 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(6 + mPosition.x, 11 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(7 + mPosition.x, 11 + mPosition.y, 20, 14, 18);
	gfx.PutPixel(8 + mPosition.x, 11 + mPosition.y, 18, 11, 14);
	gfx.PutPixel(9 + mPosition.x, 11 + mPosition.y, 18, 12, 14);
	gfx.PutPixel(10 + mPosition.x, 11 + mPosition.y, 18, 12, 14);
	gfx.PutPixel(11 + mPosition.x, 11 + mPosition.y, 21, 13, 16);
	gfx.PutPixel(12 + mPosition.x, 11 + mPosition.y, 24, 11, 15);
	gfx.PutPixel(13 + mPosition.x, 11 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(14 + mPosition.x, 11 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(15 + mPosition.x, 11 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(16 + mPosition.x, 11 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(17 + mPosition.x, 11 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(18 + mPosition.x, 11 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(19 + mPosition.x, 11 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(0 + mPosition.x, 12 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(1 + mPosition.x, 12 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(2 + mPosition.x, 12 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(3 + mPosition.x, 12 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(4 + mPosition.x, 12 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(5 + mPosition.x, 12 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(6 + mPosition.x, 12 + mPosition.y, 23, 9, 23);
	gfx.PutPixel(7 + mPosition.x, 12 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(8 + mPosition.x, 12 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(9 + mPosition.x, 12 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(10 + mPosition.x, 12 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(11 + mPosition.x, 12 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(12 + mPosition.x, 12 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(13 + mPosition.x, 12 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(14 + mPosition.x, 12 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(15 + mPosition.x, 12 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(16 + mPosition.x, 12 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(17 + mPosition.x, 12 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(18 + mPosition.x, 12 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(19 + mPosition.x, 12 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(1 + mPosition.x, 13 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(2 + mPosition.x, 13 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(3 + mPosition.x, 13 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(4 + mPosition.x, 13 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(5 + mPosition.x, 13 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(6 + mPosition.x, 13 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(7 + mPosition.x, 13 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(8 + mPosition.x, 13 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(9 + mPosition.x, 13 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(10 + mPosition.x, 13 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(11 + mPosition.x, 13 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(12 + mPosition.x, 13 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(13 + mPosition.x, 13 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(14 + mPosition.x, 13 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(15 + mPosition.x, 13 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(16 + mPosition.x, 13 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(17 + mPosition.x, 13 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(18 + mPosition.x, 13 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(1 + mPosition.x, 14 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(2 + mPosition.x, 14 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(3 + mPosition.x, 14 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(4 + mPosition.x, 14 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(5 + mPosition.x, 14 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(6 + mPosition.x, 14 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(7 + mPosition.x, 14 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(8 + mPosition.x, 14 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(9 + mPosition.x, 14 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(10 + mPosition.x, 14 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(11 + mPosition.x, 14 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(12 + mPosition.x, 14 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(13 + mPosition.x, 14 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(14 + mPosition.x, 14 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(15 + mPosition.x, 14 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(16 + mPosition.x, 14 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(17 + mPosition.x, 14 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(18 + mPosition.x, 14 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(2 + mPosition.x, 15 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(3 + mPosition.x, 15 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(4 + mPosition.x, 15 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(5 + mPosition.x, 15 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(6 + mPosition.x, 15 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(7 + mPosition.x, 15 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(8 + mPosition.x, 15 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(9 + mPosition.x, 15 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(10 + mPosition.x, 15 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(11 + mPosition.x, 15 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(12 + mPosition.x, 15 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(13 + mPosition.x, 15 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(14 + mPosition.x, 15 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(15 + mPosition.x, 15 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(16 + mPosition.x, 15 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(17 + mPosition.x, 15 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(2 + mPosition.x, 16 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(3 + mPosition.x, 16 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(4 + mPosition.x, 16 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(5 + mPosition.x, 16 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(6 + mPosition.x, 16 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(7 + mPosition.x, 16 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(8 + mPosition.x, 16 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(9 + mPosition.x, 16 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(10 + mPosition.x, 16 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(11 + mPosition.x, 16 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(12 + mPosition.x, 16 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(13 + mPosition.x, 16 + mPosition.y, 251, 192, 224);
	gfx.PutPixel(14 + mPosition.x, 16 + mPosition.y, 135, 26, 68);
	gfx.PutPixel(15 + mPosition.x, 16 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(16 + mPosition.x, 16 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(17 + mPosition.x, 16 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(3 + mPosition.x, 17 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(4 + mPosition.x, 17 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(5 + mPosition.x, 17 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(6 + mPosition.x, 17 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(7 + mPosition.x, 17 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(8 + mPosition.x, 17 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(9 + mPosition.x, 17 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(10 + mPosition.x, 17 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(11 + mPosition.x, 17 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(12 + mPosition.x, 17 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(13 + mPosition.x, 17 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(14 + mPosition.x, 17 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(15 + mPosition.x, 17 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(16 + mPosition.x, 17 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(5 + mPosition.x, 18 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(6 + mPosition.x, 18 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(7 + mPosition.x, 18 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(8 + mPosition.x, 18 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(9 + mPosition.x, 18 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(10 + mPosition.x, 18 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(11 + mPosition.x, 18 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(12 + mPosition.x, 18 + mPosition.y, 254, 221, 88);
	gfx.PutPixel(13 + mPosition.x, 18 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(14 + mPosition.x, 18 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(7 + mPosition.x, 19 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(8 + mPosition.x, 19 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(9 + mPosition.x, 19 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(10 + mPosition.x, 19 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(11 + mPosition.x, 19 + mPosition.y, 0, 0, 0);
	gfx.PutPixel(12 + mPosition.x, 19 + mPosition.y, 0, 0, 0);
}

void Dude::TogglePlayStyle()
{
	if (mPlayStyle == PlayStyle::Position)
	{
		mPlayStyle = PlayStyle::Velocity;
		mSpeed = 1;
	}
	else
	{
		mPlayStyle = PlayStyle::Position;
		mSpeed = 5;
		mVelocity = {};
	}
}
