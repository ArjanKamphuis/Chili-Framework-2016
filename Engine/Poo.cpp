#include "Poo.h"
#include "SpriteCodex.h"

void Poo::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawPoo(mPosition.x, mPosition.y, gfx);
}
