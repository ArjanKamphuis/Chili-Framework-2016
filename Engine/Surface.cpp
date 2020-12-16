#include "Surface.h"

#include <cassert>
#include <fstream>
#include "ChiliWin.h"

#define CHILI_SURFACE_EXCEPTION(filename, note) Surface::Exception(filename, note,_CRT_WIDE(__FILE__),__LINE__ )

Surface::Surface(const std::wstring& filename)
{
	try
	{
		std::ifstream fin;
		fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fin.open(filename, std::ios::binary);

		BITMAPFILEHEADER bmFileHeader = {};
		fin.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

		BITMAPINFOHEADER bmInfoHeader = {};
		fin.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

		if (bmInfoHeader.biBitCount != 24 && bmInfoHeader.biBitCount != 32)
			throw CHILI_SURFACE_EXCEPTION(filename, L"Only 24 or 32 bit images are supported.");
		if (bmInfoHeader.biCompression != BI_RGB)
			throw CHILI_SURFACE_EXCEPTION(filename, L"Only uncompressed rgb bitmaps are supported.");

		mWidth = bmInfoHeader.biWidth;

		int yStart, yEnd, dy;
		if (bmInfoHeader.biHeight < 0)
		{
			mHeight = -bmInfoHeader.biHeight;
			yStart = 0;
			yEnd = mHeight;
			dy = 1;
		}
		else
		{
			mHeight = bmInfoHeader.biHeight;
			yStart = mHeight - 1;
			yEnd = -1;
			dy = -1;
		}

		mPixels.resize(static_cast<size_t>(mWidth) * mHeight);

		fin.seekg(bmFileHeader.bfOffBits, std::ios_base::beg);
		const bool is32b = bmInfoHeader.biBitCount == 32;
		const int padding = (4 - (mWidth * 3) % 4) % 4;

		for (int y = yStart; y != yEnd; y += dy)
		{
			for (int x = 0; x < mWidth; ++x)
			{
				const unsigned char b = fin.get();
				const unsigned char g = fin.get();
				const unsigned char r = fin.get();
				PutPixel(x, y, { r, g, b });

				if (is32b)
					fin.seekg(1, std::ios_base::cur);
			}
			if (!is32b)
				fin.seekg(padding, std::ios_base::cur);
		}
	}
	catch (const std::exception& e)
	{
		const std::string message(e.what());
		throw CHILI_SURFACE_EXCEPTION(filename, std::wstring(message.begin(), message.end()));
	}
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
