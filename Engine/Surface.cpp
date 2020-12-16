#include "Surface.h"

#define FULL_WINTARD
#include "ChiliWin.h"
#include <algorithm>

namespace Gdiplus
{
	using std::min;
	using std::max;
}

#include <gdiplus.h>
#include <cassert>
#include <fstream>

#define CHILI_SURFACE_EXCEPTION(filename, note) Surface::Exception(filename, note,_CRT_WIDE(__FILE__),__LINE__ )

namespace gdi = Gdiplus;

Surface::Surface(const std::wstring& filename)
{
	if (filename.length() < 4)
		throw CHILI_SURFACE_EXCEPTION(filename, L"Surface::Surface bad file name.");

	gdi::Bitmap bitmap(filename.c_str());
	if (bitmap.GetLastStatus() != gdi::Ok)
		throw CHILI_SURFACE_EXCEPTION(filename, L"Surface::Surface failed to load file.");

	mWidth = bitmap.GetWidth();
	mHeight = bitmap.GetHeight();
	mPixels.resize(static_cast<size_t>(mWidth) * mHeight);

	const bool isAlpha = gdi::IsAlphaPixelFormat(bitmap.GetPixelFormat()) == TRUE;

	for (int y = 0; y < mHeight; ++y)
	{
		for (int x = 0; x < mWidth; ++x)
		{
			gdi::Color pixel;
			bitmap.GetPixel(x, y, &pixel);

			if (isAlpha)
				PutPixel(x, y, { pixel.GetA(), pixel.GetR(), pixel.GetG(), pixel.GetB() });
			else
				PutPixel(x, y, { pixel.GetR(), pixel.GetG(), pixel.GetB() });
		}
	}

	if (filename.find(L"pm_") != std::wstring::npos)
		BakeAlpha();
}

Surface::Surface(int width, int height)
	: mWidth(width), mHeight(height), mPixels(static_cast<size_t>(width) * height)
{
}

Surface::Surface(Surface&& rhs) noexcept
	: mWidth(rhs.mWidth), mHeight(rhs.mHeight), mPixels(std::move(rhs.mPixels))
{
	rhs.mWidth = rhs.mHeight = 0;
}

Surface& Surface::operator=(Surface&& rhs) noexcept
{
	if (this != &rhs)
	{
		mWidth = rhs.mWidth;
		mHeight = rhs.mHeight;
		mPixels = std::move(rhs.mPixels);
		rhs.mWidth = rhs.mHeight = 0;
	}
	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < mWidth);
	assert(y >= 0);
	assert(y < mHeight);
	mPixels.data()[static_cast<size_t>(y) * mWidth + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < mWidth);
	assert(y >= 0);
	assert(y < mHeight);
	return mPixels.data()[static_cast<size_t>(y) * mWidth + x];
}

RectI Surface::GetRect() const
{
	return { 0, mWidth, 0, mHeight };
}

int Surface::GetWidth() const
{
	return mWidth;
}

int Surface::GetHeight() const
{
	return mHeight;
}

const Color* Surface::Data() const
{
	return mPixels.data();
}

void Surface::BakeAlpha()
{
	for (Color& p : mPixels)
	{
		const int alpha = p.GetA();
		p.SetR(p.GetR() * alpha / 256);
		p.SetG(p.GetG() * alpha / 256);
		p.SetB(p.GetB() * alpha / 256);
	}
}

void Surface::Fill(Color c)
{
	std::fill(mPixels.begin(), mPixels.end(), c);
}

Surface::Exception::Exception(const std::wstring& filename, const std::wstring& note, const wchar_t* file, unsigned int line)
	: ChiliException(file, line, note), mFilename(filename)
{
}

std::wstring Surface::Exception::GetFullMessage() const
{
	return L"Filename: " + std::wstring(mFilename.begin(), mFilename.end()) + L"\n\n" +
		L"Note: " + GetNote() + L"\n\n" +
		L"Location: " + GetLocation();
}

std::wstring Surface::Exception::GetExceptionType() const
{
	return L"Surface exception";
}
