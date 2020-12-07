#pragma once

#include <string>
#include "Colors.h"
#include "Rect.h"

class Surface
{
public:
	Surface() = default;
	Surface(const std::string& filename);
	Surface(int width, int height);
	Surface(const Surface& rhs);
	Surface(Surface&& rhs) noexcept;
	Surface& operator=(const Surface& rhs);
	Surface& operator=(Surface&& rhs) noexcept;
	~Surface() noexcept;

	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;

	RectI GetRect() const;
	int GetWidth() const;
	int GetHeight() const;

private:
	Color* mPixels = nullptr;
	int mWidth = 0;
	int mHeight = 0;
};
