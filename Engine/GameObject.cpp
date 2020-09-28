#include "GameObject.h"

void GameObject::Update(float dt)
{
	mPosition.X += mVelocity.X * dt;
	mPosition.Y += mVelocity.Y * dt;

	float screenWidth = static_cast<float>(Graphics::ScreenWidth);
	float screenHeight = static_cast<float>(Graphics::ScreenHeight);

	if (mPosition.X < 0.0f)
	{
		mPosition.X = 0.0f;
		mVelocity.X *= mBouncing ? -1.0f : 0.0f;

	}
	else if (mPosition.X + mSize >= screenWidth)
	{
		mPosition.X = screenWidth - mSize - 1.0f;
		mVelocity.X *= mBouncing ? -1.0f : 0.0f;
	}

	if (mPosition.Y < 0.0f)
	{
		mPosition.Y = 0.0f;
		mVelocity.Y *= mBouncing ? -1.0f : 0.0f;

	}
	else if (mPosition.Y + mSize >= screenHeight)
	{
		mPosition.Y = screenHeight - mSize - 1.0f;
		mVelocity.Y *= mBouncing ? -1.0f : 0.0f;
	}
}

void GameObject::Respawn(float x, float y, float vx, float vy)
{
	mPosition = { x, y };
	mVelocity = { vx, vy };
}

bool GameObject::OverlapTest(const GameObject& rhs) const
{
	float range = 0.5f * (mSize + rhs.GetSize());
	return abs(mPosition.X - rhs.GetPosition().X) <= range && abs(mPosition.Y - rhs.GetPosition().Y) <= range;
}

GameObject::Point GameObject::GetPosition() const
{
	return mPosition;
}

float GameObject::GetSize() const
{
	return mSize;
}

GameObject::GameObject(float size)
	: mSize(size)
{
}
