#pragma once

#include "Graphics.h"
#include "Surface.h"
#include "Vec2.h"

class Font
{
public:
	Font(const std::string& filename, Color chroma = Colors::White);
	void DrawText(Graphics& gfx, const std::string& text, const Vec2I& pos, Color color) const;

private:
	RectI MapGlyphRect(char c) const;

private:
	Surface mSurface;
	int mGlyphWidth;
	int mGlyphHeight;
	Color mChroma;

	static constexpr int mNumColums = 32;
	static constexpr int mNumRows = 3;
	static constexpr char mFirstChar = ' ';
	static constexpr char mLastChar = '~';
};

