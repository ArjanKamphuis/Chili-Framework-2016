#pragma once

#include <string>
#include <vector>
#include "ChiliException.h"
#include "Colors.h"
#include "Rect.h"

class Surface
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception(const std::wstring& filename, const std::wstring& note, const wchar_t* file, unsigned int line);
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;

	private:
		const std::wstring mFilename;
	};

public:
	Surface() = default;
	Surface(const std::wstring& filename);
	Surface(int width, int height);
	Surface(const Surface& rhs) = default;
	Surface& operator=(const Surface& rhs) = default;
	Surface(Surface&& rhs) noexcept;
	Surface& operator=(Surface&& rhs) noexcept;

	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;

	RectI GetRect() const;
	int GetWidth() const;
	int GetHeight() const;

	void BakeAlpha();
	void Fill(Color c);
	const Color* Data() const;

private:
	std::vector<Color> mPixels;
	int mWidth = 0;
	int mHeight = 0;
};
