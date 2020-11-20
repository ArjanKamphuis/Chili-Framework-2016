#include "Font.h"
#include <cassert>

Font::Font(const std::string& filename, Color chroma)
	: mSurface(filename), mChroma(chroma)
	, mGlyphWidth(mSurface.GetWidth() / mNumColums)
	, mGlyphHeight(mSurface.GetHeight() / mNumRows)
{
	assert(mGlyphWidth * mNumColums == mSurface.GetWidth());
	assert(mGlyphHeight * mNumRows == mSurface.GetHeight());
}

void Font::DrawText(Graphics& gfx, const std::string& text, const Vec2I& pos, Color color) const
{
	Vec2I currPos = pos;
	for (char c : text)
	{
		if (c == '\n')
		{
			currPos.X = pos.X;
			currPos.Y += mGlyphHeight;
			continue;
		}

		if (c >= mFirstChar + 1 && c <= mLastChar)
			gfx.DrawSpriteSubstitude(currPos.X, currPos.Y, color, MapGlyphRect(c), mSurface, mChroma);
		currPos.X += mGlyphWidth;
	}
}

RectI Font::MapGlyphRect(char c) const
{
	assert(c >= mFirstChar && c <= mLastChar);

	const int glyphIndex = c - ' ';
	const int yGlyph = glyphIndex / mNumColums;
	const int xGlyph = glyphIndex % mNumColums;

	return RectI({ xGlyph * mGlyphWidth, yGlyph * mGlyphHeight }, mGlyphWidth, mGlyphHeight);
}
