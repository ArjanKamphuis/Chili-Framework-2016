#pragma once

#include "RectI.h"
#include "SpriteCodex.h"
#include "Mouse.h"
#include "Sound.h"

class SelectionMenu
{
public:
	enum class Size { Small, Medium, Large, Count, Invalid };

private:
	class Entry
	{
	public:
		Entry() = default;
		Entry(Size s, const Vec2I& pos);

		void Draw(Graphics& gfx) const;
		bool IsHit(const Vec2I& pt) const;
		Size GetSize() const;

		void ResetHighlight();
		void SetHighlight();
		bool IsHighlighted() const;

	private:
		static void DrawSizeText(Size s, const Vec2I& pos, Graphics& gfx);

	private:
		static constexpr int mHighlightThickness = 6;
		static constexpr Color mHighlightColor = Colors::Yellow;
		bool mHighlighted = false;
		Size mSize = Size::Invalid;
		RectI mRect;
	};

public:
	SelectionMenu(const Vec2I& pos);
	Size ProcessMouse(const Mouse::Event& e);
	void Draw(Graphics& gfx) const;

private:
	void ResetHighlights();

private:
	static constexpr int mVerticalSpacing = SpriteCodex::sizeselHeight * 2;
	Sound mSndHover = { L"data/menu_boop.wav " };
	Entry mEntries[static_cast<int>(Size::Count)];
};

