#pragma once

#include "Graphics.h"

namespace SpriteEffect
{
	class Chroma
	{
	public:
		Chroma(Color c)
			: mChroma(c)
		{}
		void operator()(Graphics& gfx, Color cSrc, int xDest, int yDest) const
		{
			if (cSrc != mChroma)
				gfx.PutPixel(xDest, yDest, cSrc);
		}

	private:
		Color mChroma;
	};

	class Substitution
	{
	public:
		Substitution(Color c, Color s)
			: mChroma(c), mSub(s)
		{}
		void operator()(Graphics& gfx, Color cSrc, int xDest, int yDest) const
		{
			if (cSrc != mChroma)
				gfx.PutPixel(xDest, yDest, mSub);
		}

	private:
		Color mChroma;
		Color mSub;
	};

	class Copy
	{
	public:
		void operator()(Graphics& gfx, Color cSrc, int xDest, int yDest) const
		{
			gfx.PutPixel(xDest, yDest, cSrc);
		}
	};

	class Ghost
	{
	public:
		Ghost(Color c)
			: mChroma(c)
		{}
		void operator()(Graphics& gfx, Color cSrc, int xDest, int yDest) const
		{
			if (cSrc != mChroma)
			{
				const Color cDst = gfx.GetPixel(xDest, yDest);
				const Color blend = {
					static_cast<unsigned char>(((cDst.GetR() + cSrc.GetR()) / 2)),
					static_cast<unsigned char>(((cDst.GetG() + cSrc.GetG()) / 2)),
					static_cast<unsigned char>(((cDst.GetB() + cSrc.GetB()) / 2))
				};
				gfx.PutPixel(xDest, yDest, blend);
			}
		}

	private:
		Color mChroma;
	};

	class DissolveHalfTint
	{
	public:
		DissolveHalfTint(Color chroma, Color tint, float percent)
			: mChroma(chroma)
			, mTintPre((tint.dword >> 1u) & 0b01111111011111110111111101111111u)
			, mFilled(static_cast<int>(static_cast<float>(mHeight) * percent))
		{}
		void operator()(Graphics& gfx, Color src, int xDest, int yDest) const
		{
			if (src != mChroma && (yDest & mHeightMask) < mFilled)
			{
				const Color blend = mTintPre.dword + ((src.dword >> 1u) & 0b01111111011111110111111101111111u);
				gfx.PutPixel(xDest, yDest, blend);
			}
		}

	private:
		Color mChroma;
		Color mTintPre;
		static constexpr int mHeight = 4;
		static constexpr int mHeightMask = mHeight - 1;
		int mFilled;
	};

	class AlphaBlendBaked
	{
	public:
		void operator()(Graphics& gfx, Color src, int xDest, int yDest) const
		{
			const Color dst = gfx.GetPixel(xDest, yDest);
			const int cAlpha = 255 - src.GetA();

			const int rb = (((dst.dword & 0xFF00FFu) * cAlpha) >> 8) & 0xFF00FFu;
			const int g = (((dst.dword & 0x00FF00u) * cAlpha) >> 8) & 0x00FF00u;

			gfx.PutPixel(xDest, yDest, rb + g + src.dword);
		}
	};
}
