#pragma once
#include <algorithm>
enum class ItemType : std::size_t 
{Weapon,Armor,Jewelry,Chest,Shrine,Key,Gold, numbTypes, None};
enum class WeaponClass : std::size_t 
{ Sword, Axe, PoleAxe, Bow, Staff, Wand, numbTypes, None };
enum class ArmorClass : std::size_t 
{ Body, Helm, Gloves, Boots, Shield, numbTypes, None };
enum class PotionClass : std::size_t 
{ Health, Mana, Invisible, numbTypes, None };
enum class JewelryClass : std::size_t
{Ring,Amulet,numbTypes};
enum class KeyClass : std::size_t
{Single, Ghost,numbTypes};
enum class ItemClass : std::size_t
{Crude,Crafted,Magic,Rare,numbTypes};

enum EntityTypes : std::size_t
{
   entityWeapon,
   entityArmor,
   entityGloves,
   entityBoots,
   entityHelm,
   entityRingA,
   entityRingB,
   entityAmulet,
   entitySheild,
   entityChest,
   entityBook,
   entityPotion,
   entityPlayer,
   entityEnemy,
   entityTile,
   entityExplosion,
   entityAnimation,
   entityBody

};

enum  GroupLabels : std::size_t
{
	groupMapLayer1,
	groupMapLayer2,
	groupActors,
	groupPlayers,
	groupEnemies,
	groupCollider,
	groupItems,
	groupChest,
	groupRender,
	groupLight,
	groupAmmo,
	groupNumGroups
};


