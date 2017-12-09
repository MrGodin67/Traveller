#include "stdafx.h"
#include "ActorInventory.h"
#include "Actor.h"




ActorInventory::~ActorInventory()
{
	
}

Item* ActorInventory::Add(const Item & item)
{
	if (m_itemCounter < _inventoryMaxItems)
	{
		Item* ptr = new Item(item);
		std::unique_ptr<Item> uPtr{ ptr };
		m_items.emplace_back(std::move(uPtr));
		m_itemCounter++;
		return ptr;
	}
	return nullptr;
}

void ActorInventory::Refresh()
{
	// removes inactive items
	
	m_items.erase(std::remove_if(std::begin(m_items), std::end(m_items),
		[=](const std::unique_ptr<Item>& vec_item)
	{
		return !vec_item->active;
	}), std::end(m_items));
	
}

void ActorInventory::Remove(Item * item)
{
	item->active = false;
	m_equippedItems.RemoveItem(item->type);
}

std::size_t ActorInventory::size()
{
	return m_items.size();
}


std::vector<std::unique_ptr<Item>>& ActorInventory::GetItems()
{
	return m_items;
}


