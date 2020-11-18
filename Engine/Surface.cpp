#include "Surface.h"

#include <assert.h>

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
