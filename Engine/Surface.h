#pragma once

#include <string>
#include "Colors.h"
#include "RectI.h"

class Surface
{
public:
	Surface(const std::string& filename);
	Surface(int width, int height);
	Surface(const Surface& rhs);
	Surface& operator=(const Surface& rhs);
	~Surface();

	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;

	RectI GetRect() const;
	int GetWidth() const;
	int GetHeight() const;

private:
	Color* mPixels = nullptr;
	int mWidth;
	int mHeight;
};