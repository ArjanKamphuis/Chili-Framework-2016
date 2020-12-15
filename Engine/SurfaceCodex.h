#pragma once

#include <string>
#include <vector>
#include "ChiliUtil.h"
#include "Surface.h"

class SurfaceCodex
{
private:
	class Entry
	{
	public:
		Entry(const std::string& key, const Surface* pSurface);
		bool operator<(const Entry& rhs) const;

		const std::string& GetKey() const;
		const Surface* GetSurface() const;
		void DeleteSurface();

	private:
		std::string mKey;
		const Surface* mSurface;
	};

public:
	static const Surface* Retreive(const std::string& key);
	static void Purge();

private:
	SurfaceCodex() = default;
	~SurfaceCodex();

	const Surface* _Retreive(const std::string& key);
	void _Purge();
	static SurfaceCodex& Get();

private:
	std::vector<Entry> mEntries;
};

