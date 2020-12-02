#pragma once

#include <vector>
#include "Graphics.h"

class Background
{
public:
	Background(const RectI& bgRegion, int gridWidth, int gridHeight, const std::string& map);
	void Draw(Graphics& gfx) const;

private:
	int GetTileAt(int x, int y) const;

private:
	Surface mTileset = "Images/floor5.bmp";
	Vec2I mOrigin;
	std::vector<RectI> mTileRects;
	std::vector<int> mTiles;
	int mNumTiles = 11;
	int mTileSize = 32;
	int mGridWidth;
	int mGridHeight;
};

