#pragma once

#include "Components.h"
#include "SpriteComp.h"
enum class ItemTypes : std::size_t {  Key, Weapon, Potion, Gold, Chest, Armour,Shrine,Book, numbTypes,None };
enum class WeaponSubTypes : std::size_t { Sword, Axe, PoleAxe,Bow,Staff,Wand,numbTypes,None};
enum class ArmorSubTypes : std::size_t {  Body, Helm, Gloves, Boots, Shield, numbTypes,None };
enum class PotionSubTypes : std::size_t {Health, Mana, Invisible, numbTypes,None };
enum class EquippedItems : std::size_t {body,weapon,armor,boots,gloves,helm,ring1,ring2,amulet,numbEquppedItems,none};
enum class ItemClass : std::size_t { basic,crafted,magic,rare };

class Item : public Component
{
public:
	EquippedItems type = EquippedItems::none;
	std::wstring name = L"";
	std::wstring description = L"";
	bool active = true;
	bool equipped = false;
	bool visible = false;
	bool selected = false;
	ID2D1Bitmap* image;
	RectF srcRect;
	RectF destRect;
	

};
class Weapon : public Item
{
public:
	Weapon();
	
	Weapon(const WeaponSubTypes& sub_type,ID2D1Bitmap* image, const RectF& srcRect, const RectF& destRect,
		const std::wstring& name, const std::wstring& description)
	{
		this->image = image;
		this->srcRect = srcRect;
		this->destRect = destRect;
		this->name = name;
		this->description = description;
		this->subType = sub_type;
		this->type = EquippedItems::weapon;
	}
	WeaponSubTypes subType;
	float damage;
	float bonus;
	bool magic;
	void Draw()override;

};
