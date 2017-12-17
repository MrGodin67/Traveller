#include "stdafx.h"
#include "ColliderComponent.h"
#include "Locator.h"
void Collider::Draw()
{

	{
		if (doDraw)
		{
			Locator::Graphics()->DrawRectangle(owner->Get<Transform>().Matrix(),
				owner->Get<Transform>().Rect().ToD2D(),
				D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}
