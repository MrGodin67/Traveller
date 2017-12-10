#pragma once
#include "Components.h"
class ItemFactory
{
	static Item BasicAxe;
public:
	ItemFactory();
	~ItemFactory();

	static Item GetWeapon(const WeaponSubTypes& type, const int& ItemClass);
};

