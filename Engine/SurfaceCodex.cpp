#include "SurfaceCodex.h"

#include <algorithm>

SurfaceCodex::Entry::Entry(const std::string& key, const Surface* pSurface)
	: mKey(key), mSurface(pSurface)
{
}

bool SurfaceCodex::Entry::operator<(const Entry& rhs) const
{
	return mKey < rhs.mKey;
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
	const auto it = binary_find(mEntries.begin(), mEntries.end(), key,
		[](const Entry& e) { return e.GetKey(); });
	if (it == mEntries.end())
	{
		const Entry e(key, new Surface(key));
		mEntries.insert(std::lower_bound(mEntries.begin(), mEntries.end(), e), e);
		return e.GetSurface();
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
