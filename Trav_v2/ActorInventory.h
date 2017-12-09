#pragma once
#include "Components.h"
#include "ActorEquippedItems.h"
class Actor;
const std::size_t _inventoryMaxItems = 20;
class ActorInventory
{
	
	std::size_t m_itemCounter = 0;
	std::vector<std::unique_ptr<Item>> m_items;
	Item* m_selectedItem;
	bool m_visible;
	ActorEquippedItems& m_equippedItems;

public:
	ActorInventory() = default;
	ActorInventory(ActorEquippedItems& eqItems,Actor* owner)
		:Owner(owner),m_equippedItems(eqItems)
	{
		int x = 0;
	}
	virtual ~ActorInventory();
	Actor* Owner = nullptr;
	Item* Add(const Item & item);
	void Refresh();
	void Remove(Item* item);
	std::size_t size();
	virtual std::vector<std::unique_ptr<Item>>& GetItems();
	
	
};

