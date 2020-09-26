#include "Dude.h"
#include "SpriteCodex.h"

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
	SpriteCodex::DrawDude(mPosition.x, mPosition.y, gfx);
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
