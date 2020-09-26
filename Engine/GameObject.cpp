#include "GameObject.h"

void GameObject::Update()
{
	mPosition.x += mVelocity.x;
	mPosition.y += mVelocity.y;

	if (mPosition.x < 0)
	{
		mPosition.x = 0;
		mVelocity.x *= mBouncing ? -1 : 0;

	}
	else if (mPosition.x + mSize >= Graphics::ScreenWidth)
	{
		mPosition.x = Graphics::ScreenWidth - mSize - 1;
		mVelocity.x *= mBouncing ? -1 : 0;
	}

	if (mPosition.y < 0)
	{
		mPosition.y = 0;
		mVelocity.y *= mBouncing ? -1 : 0;

	}
	else if (mPosition.y + mSize >= Graphics::ScreenHeight)
	{
		mPosition.y = Graphics::ScreenHeight - mSize - 1;
		mVelocity.y *= mBouncing ? -1 : 0;
	}
}

void GameObject::Respawn(int x, int y, int vx, int vy)
{
	mPosition = { x, y };
	mVelocity = { vx, vy };
}

bool GameObject::OverlapTest(const GameObject& rhs) const
{
	int range = (mSize + rhs.GetSize()) / 2;
	return abs(mPosition.x - rhs.GetPosition().x) <= range && abs(mPosition.y - rhs.GetPosition().y) <= range;
}

GameObject::Point GameObject::GetPosition() const
{
	return mPosition;
}

int GameObject::GetSize() const
{
	return mSize;
}

GameObject::GameObject(int size)
	: mSize(size)
{
}
