#include "Dude.h"
#include "SpriteCodex.h"

Dude::Dude()
	: GameObject(20)
{
	ChangePlayStyle(PlayStyle::Mouse);
}

void Dude::HandleInput(Keyboard& kbd, const Mouse& mouse)
{
	if (kbd.KeyIsPressed('1'))
		ChangePlayStyle(PlayStyle::Position);
	if (kbd.KeyIsPressed('2'))
		ChangePlayStyle(PlayStyle::Velocity);
	if (kbd.KeyIsPressed('3'))
		ChangePlayStyle(PlayStyle::Mouse);

	switch (mPlayStyle)
	{
	case PlayStyle::Position:
		mVelocity = {};

		if (kbd.KeyIsDown(VK_LEFT))
			mVelocity.X -= 1.0f;
		if (kbd.KeyIsDown(VK_RIGHT))
			mVelocity.X += 1.0f;
		if (kbd.KeyIsDown(VK_UP))
			mVelocity.Y -= 1.0f;
		if (kbd.KeyIsDown(VK_DOWN))
			mVelocity.Y += 1.0f;

		mVelocity.Normalize() *= mSpeed;
		break;

	case PlayStyle::Velocity:
		if (kbd.KeyIsPressed(VK_LEFT))
			mVelocity.X -= mSpeed;
		if (kbd.KeyIsPressed(VK_RIGHT))
			mVelocity.X += mSpeed;
		if (kbd.KeyIsPressed(VK_UP))
			mVelocity.Y -= mSpeed;
		if (kbd.KeyIsPressed(VK_DOWN))
			mVelocity.Y += mSpeed;
		break;

	case PlayStyle::Mouse:
		mVelocity = {};
		if (mouse.LeftIsPressed())
		{
			const Vec2 center = mPosition + Vec2(0.5f * mSize, 0.5f * mSize);
			const Vec2 to = Vec2(static_cast<float>(mouse.GetPosX()), static_cast<float>(mouse.GetPosY())) - center;
			if (to.GetLengthSq() > 2.0f)
				mVelocity = to.GetNormalized() * mSpeed;
		}
		break;
	}
}

void Dude::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawDude(static_cast<int>(mPosition.X), static_cast<int>(mPosition.Y), gfx);
}

void Dude::ChangePlayStyle(PlayStyle style)
{
	mPlayStyle = style;
	switch (style)
	{
	case PlayStyle::Mouse:
	case PlayStyle::Position:
		mSpeed = mPositionSpeed;
		break;
	case PlayStyle::Velocity:
		mSpeed = mVelocitySpeed;
		break;
	}
}
