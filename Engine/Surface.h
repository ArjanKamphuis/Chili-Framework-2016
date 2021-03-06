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
		Exception(const std::string& filename, const std::wstring& note, const wchar_t* file, unsigned int line);
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;

	private:
		const std::string mFilename;
	};

public:
	Surface() = default;
	Surface(const std::string& filename);
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

	void Fill(Color c);
	const Color* Data() const;

private:
	std::vector<Color> mPixels;
	int mWidth = 0;
	int mHeight = 0;
};
