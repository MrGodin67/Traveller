#include "stdafx.h"
#include "ItemFactory.h"

Item ItemFactory::BasicAxe = Item();

ItemFactory::ItemFactory()
{
}


ItemFactory::~ItemFactory()
{
}

Item ItemFactory::GetWeapon(const WeaponSubTypes & type, const int & ItemClass)
{
	return Item();
}
