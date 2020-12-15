#include "SurfaceCodex.h"

#include <algorithm>

SurfaceCodex::Entry::Entry(const std::string& key, const Surface* pSurface)
	: mKey(key), mSurface(pSurface)
{
}

const std::string& SurfaceCodex::Entry::GetKey() const
{
	return mKey;
}

const Surface* SurfaceCodex::Entry::GetSurface() const
{
	return mSurface;
}

void SurfaceCodex::Entry::DeleteSurface()
{
	delete mSurface;
}

const Surface* SurfaceCodex::Retreive(const std::string& key)
{
	return Get()._Retreive(key);
}

void SurfaceCodex::Purge()
{
	return Get()._Purge();
}

SurfaceCodex::~SurfaceCodex()
{
	for (Entry& e : mEntries)
		e.DeleteSurface();
}

const Surface* SurfaceCodex::_Retreive(const std::string& key)
{
	const auto it = std::find_if(mEntries.begin(), mEntries.end(), [&key](const Entry& e) { return key == e.GetKey(); });
	if (it == mEntries.end())
	{
		Surface* pSurface = new Surface(key);
		mEntries.emplace_back(key, pSurface);
		return pSurface;
	}
	else
		return it->GetSurface();
}

void SurfaceCodex::_Purge()
{
	for (Entry& e : mEntries)
		e.DeleteSurface();
	mEntries.clear();
}

SurfaceCodex& SurfaceCodex::Get()
{
	static SurfaceCodex codex;
	return codex;
}
