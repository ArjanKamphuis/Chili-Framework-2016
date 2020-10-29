#include "SelectionMenu.h"

SelectionMenu::Entry::Entry(Size s, const Vec2I& pos)
	: mSize(s), mRect(RectI::FromCenter(pos, SpriteCodex::sizeselWidth / 2, SpriteCodex::sizeselHeight / 2))
{
}

void SelectionMenu::Entry::Draw(Graphics& gfx) const
{
	if (mHighlighted)
		gfx.DrawRect(mRect.GetExpanded(mHighlightThickness), mHighlightColor);
	gfx.DrawRect(mRect, Colors::Black);
	DrawSizeText(mSize, mRect.GetCenter(), gfx);
}

bool SelectionMenu::Entry::IsHit(const Vec2I& pt) const
{
	return mRect.Contains(pt);
}

SelectionMenu::Size SelectionMenu::Entry::GetSize() const
{
	return mSize;
}

void SelectionMenu::Entry::ResetHighlight()
{
	mHighlighted = false;
}

void SelectionMenu::Entry::SetHighlight()
{
	mHighlighted = true;
}

bool SelectionMenu::Entry::IsHighlighted() const
{
	return mHighlighted;
}

void SelectionMenu::Entry::DrawSizeText(Size s, const Vec2I& pos, Graphics& gfx)
{
	switch (s)
	{
	case Size::Small: SpriteCodex::DrawSmall(pos, gfx); break;
	case Size::Medium: SpriteCodex::DrawMedium(pos, gfx); break;
	case Size::Large: SpriteCodex::DrawLarge(pos, gfx); break;
	}
}

SelectionMenu::SelectionMenu(const Vec2I& pos)
{
	Vec2I center = pos;
	for (int i = 0; i < static_cast<int>(Size::Count); ++i)
	{
		mEntries[i] = { static_cast<Size>(i), center };
		center.Y += mVerticalSpacing;
	}
}

SelectionMenu::Size SelectionMenu::ProcessMouse(const Mouse::Event& e)
{
	switch (e.GetType())
	{
	case Mouse::Event::Type::Move:
		for (Entry& entry : mEntries)
		{
			if (entry.IsHit(e.GetPos()))
			{
				if (!entry.IsHighlighted())
				{
					ResetHighlights();
					entry.SetHighlight();
					mSndHover.Play();
				}
				return Size::Invalid;
			}
		}
		ResetHighlights();
		break;
	case Mouse::Event::Type::LPress:
		for (Entry& entry : mEntries)
			if (entry.IsHit(e.GetPos()))
				return entry.GetSize();
		break;
	}
	return Size::Invalid;
}

void SelectionMenu::Draw(Graphics& gfx) const
{
	for (const Entry& entry : mEntries)
		entry.Draw(gfx);
}

void SelectionMenu::ResetHighlights()
{
	for (Entry& entry : mEntries)
		entry.ResetHighlight();
}
