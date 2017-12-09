#include "stdafx.h"
#include "ItemComp.h"

Weapon::Weapon()
{
	type = EquippedItems::weapon;
}

void Weapon::Draw()
{
	Locator::Graphics()->DrawSprite(D2D1::Matrix3x2F::Identity(),
		destRect.ToD2D(), image, &srcRect.ToD2D());
}
