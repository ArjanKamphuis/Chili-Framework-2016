#include "Poo.h"
#include "SpriteCodex.h"

void Poo::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawPoo(static_cast<int>(mPosition.X), static_cast<int>(mPosition.Y), gfx);
}
