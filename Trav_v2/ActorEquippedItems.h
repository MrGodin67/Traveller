#pragma once
#include "Components.h"
class ActorInventory;
class ActorEquippedItems
{

	friend class ActorInventory;
	std::unordered_map<EquippedItems, Item*> m_items;
	bool it;
public:
	ActorEquippedItems();
	~ActorEquippedItems();
	Item* GetItem(const EquippedItems& name);
	void RemoveItem(const EquippedItems& name);
	void Add(const EquippedItems& name, Item* item);
};

