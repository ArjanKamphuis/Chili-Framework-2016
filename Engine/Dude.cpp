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
		mVelocity = {};

		if (kbd.KeyIsDown(VK_LEFT))
			mVelocity.X -= mSpeed;
		if (kbd.KeyIsDown(VK_RIGHT))
			mVelocity.X += mSpeed;
		if (kbd.KeyIsDown(VK_UP))
			mVelocity.Y -= mSpeed;
		if (kbd.KeyIsDown(VK_DOWN))
			mVelocity.Y += mSpeed;
	}
	else
	{
		if (kbd.KeyIsPressed(VK_LEFT))
			mVelocity.X -= mSpeed;
		if (kbd.KeyIsPressed(VK_RIGHT))
			mVelocity.X += mSpeed;
		if (kbd.KeyIsPressed(VK_UP))
			mVelocity.Y -= mSpeed;
		if (kbd.KeyIsPressed(VK_DOWN))
			mVelocity.Y += mSpeed;
	}
}

void Dude::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawDude(static_cast<int>(mPosition.X), static_cast<int>(mPosition.Y), gfx);
}

void Dude::TogglePlayStyle()
{
	if (mPlayStyle == PlayStyle::Position)
	{
		mPlayStyle = PlayStyle::Velocity;
		mSpeed = mVelocitySpeed;
	}
	else
	{
		mPlayStyle = PlayStyle::Position;
		mSpeed = mPositionSpeed;
	}
}
