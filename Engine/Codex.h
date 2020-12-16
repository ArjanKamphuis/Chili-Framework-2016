#pragma once

#include <string>
#include <vector>
#include "ChiliUtil.h"

template <class T>
class Codex
{
private:
	class Entry
	{
	public:
		Entry(const std::wstring& key, const T* pResource)
			: mKey(key), mResource(pResource)
		{
		}
		bool operator<(const Entry& rhs) const
		{
			return mKey < rhs.mKey;
		}

		const std::wstring& GetKey() const
		{
			return mKey;
		}
		const T* GetResource() const
		{
			return mResource;
		}
		void DeleteResource()
		{
			delete mResource;
		}

	private:
		std::wstring mKey;
		const T* mResource;
	};

public:
	static const T* Retreive(const std::wstring& key)
	{
		return Get()._Retreive(key);
	}
	static void Purge()
	{
		return Get()._Purge();
	}

private:
	Codex() = default;
	~Codex()
	{
		for (Entry& e : mEntries)
			e.DeleteResource();
	}

	const T* _Retreive(const std::wstring& key)
	{
		const auto it = binary_find(mEntries.begin(), mEntries.end(), key,
			[](const Entry& e) { return e.GetKey(); });
		if (it == mEntries.end())
		{
			const Entry e(key, new T(key));
			mEntries.insert(std::lower_bound(mEntries.begin(), mEntries.end(), e), e);
			return e.GetResource();
		}
		else
			return it->GetResource();
	}
	void _Purge()
	{
		for (Entry& e : mEntries)
			e.DeleteResource();
		mEntries.clear();
	}
	static Codex& Get()
	{
		static Codex codex;
		return codex;
	}

private:
	std::vector<Entry> mEntries;
};

