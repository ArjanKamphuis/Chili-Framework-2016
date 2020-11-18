#include "Surface.h"

#include <assert.h>
#include <fstream>
#include "ChiliWin.h"

Surface::Surface(const std::string& filename)
{
	std::ifstream fin(filename, std::ios::binary);
	assert(fin);

	BITMAPFILEHEADER bmFileHeader;
	fin.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

	BITMAPINFOHEADER bmInfoHeader;
	fin.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

	assert(bmInfoHeader.biBitCount == 24);
	assert(bmInfoHeader.biCompression == BI_RGB);

	mWidth = bmInfoHeader.biWidth;
	mHeight = bmInfoHeader.biHeight;
	mPixels = new Color[mWidth * mHeight];

	fin.seekg(bmFileHeader.bfOffBits, std::ios_base::beg);
	const int padding = (4 - (mWidth * 3) % 4) % 4;

	for (int y = mHeight - 1; y >= 0; --y)
	{
		for (int x = 0; x < mWidth; ++x)
		{
			const unsigned char b = fin.get();
			const unsigned char g = fin.get();
			const unsigned char r = fin.get();
			PutPixel(x, y, { r, g, b });
		}
		fin.seekg(padding, std::ios_base::cur);
	}
}

Surface::Surface(int width, int height)
	: mWidth(width), mHeight(height), mPixels(new Color[width * height])
{
}

Surface::Surface(const Surface& rhs)
	: Surface(rhs.mWidth, rhs.mHeight)
{
	for (int i = 0; i < mWidth * mHeight; ++i)
		mPixels[i] = rhs.mPixels[i];
}

Surface& Surface::operator=(const Surface& rhs)
{
	if (this != &rhs)
	{
		mWidth = rhs.mWidth;
		mHeight = rhs.mHeight;

		const int nPixels = mWidth * mHeight;

		delete[] mPixels;
		mPixels = new Color[nPixels];

		for (int i = 0; i < nPixels; ++i)
			mPixels[i] = rhs.mPixels[i];
	}
	return *this;
}

Surface::~Surface()
{
	delete[] mPixels;
	mPixels = nullptr;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < mWidth);
	assert(y >= 0);
	assert(y < mHeight);
	mPixels[y * mWidth + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < mWidth);
	assert(y >= 0);
	assert(y < mHeight);
	return mPixels[y * mWidth + x];
}

int Surface::GetWidth() const
{
	return mWidth;
}

int Surface::GetHeight() const
{
	return mHeight;
}
