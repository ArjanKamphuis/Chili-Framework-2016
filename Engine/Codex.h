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
		const auto it = std::lower_bound(mEntries.begin(), mEntries.end(), key,
			[](const Entry& e, const std::wstring& key)
			{ 
				return e.GetKey() < key; 
			}
		);

		if (it == mEntries.end() || it->GetKey() != key)
			return mEntries.emplace(it, key, new T(key))->GetResource();
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

