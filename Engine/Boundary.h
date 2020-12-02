#pragma once

#include "Rect.h"

template<typename T>
class Boundary
{
public:
	Boundary(const Rect<T>& boundaryRect)
		: mRect(boundaryRect)
	{
	}
	template<class Entity>
	void Adjust(Entity& e) const
	{
		const Rect<T> entityRect = e.GetHitbox();
		if (entityRect.Left < mRect.Left)
			e.DisplaceBy({ mRect.Left - entityRect.Left, static_cast<T>(0) });
		else if (entityRect.Right > mRect.Right)
			e.DisplaceBy({ mRect.Right - entityRect.Right, static_cast<T>(0) });
		if (entityRect.Top < mRect.Top)
			e.DisplaceBy({ static_cast<T>(0), mRect.Top - entityRect.Top });
		if (entityRect.Bottom > mRect.Bottom)
			e.DisplaceBy({ static_cast<T>(0), mRect.Bottom - entityRect.Bottom });
	}
	const Rect<T>& GetRect() const
	{
		return mRect;
	}

private:
	Rect<T> mRect;
};

using BoundaryF = Boundary<float>;
using BoundaryI = Boundary<int>;
