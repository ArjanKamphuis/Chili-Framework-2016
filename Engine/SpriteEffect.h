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
}
