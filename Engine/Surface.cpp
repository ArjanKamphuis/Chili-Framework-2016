#include "Surface.h"

#include <cassert>
#include <fstream>
#include "ChiliWin.h"

Surface::Surface(const std::string& filename)
{
	std::ifstream fin(filename, std::ios::binary);
	assert(fin);

	BITMAPFILEHEADER bmFileHeader = {};
	fin.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

	BITMAPINFOHEADER bmInfoHeader = {};
	fin.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

	assert(bmInfoHeader.biBitCount == 24 || bmInfoHeader.biBitCount == 32);
	assert(bmInfoHeader.biCompression == BI_RGB);

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

	mPixels = std::make_unique<Color[]>(static_cast<size_t>(mWidth) * mHeight);

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

Surface::Surface(int width, int height)
	: mWidth(width), mHeight(height), mPixels(std::make_unique<Color[]>(static_cast<size_t>(width) * height))
{
}

Surface::Surface(const Surface& rhs)
	: Surface(rhs.mWidth, rhs.mHeight)
{
	for (int i = 0; i < mWidth * mHeight; ++i)
		mPixels[i] = rhs.mPixels[i];
}

Surface::Surface(Surface&& rhs) noexcept
	: mWidth(rhs.mWidth), mHeight(rhs.mHeight), mPixels(std::move(rhs.mPixels))
{
	rhs.mWidth = rhs.mHeight = 0;
}

Surface& Surface::operator=(const Surface& rhs)
{
	if (this != &rhs)
	{
		mWidth = rhs.mWidth;
		mHeight = rhs.mHeight;

		const int nPixels = mWidth * mHeight;

		mPixels = std::make_unique<Color[]>(nPixels);

		for (int i = 0; i < nPixels; ++i)
			mPixels[i] = rhs.mPixels[i];
	}
	return *this;
}

Surface& Surface::operator=(Surface&& rhs) noexcept
{
	if (this != &rhs)
	{
		mWidth = rhs.mWidth;
		mHeight = rhs.mHeight;

		mPixels = std::move(rhs.mPixels);

		rhs.mWidth = rhs.mHeight = 0;
		rhs.mPixels = nullptr;
	}
	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < mWidth);
	assert(y >= 0);
	assert(y < mHeight);
	mPixels[static_cast<size_t>(y) * mWidth + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < mWidth);
	assert(y >= 0);
	assert(y < mHeight);
	return mPixels[y * mWidth + x];
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
