#include "stdafx.h"
#include "ActorEquippedItems.h"


ActorEquippedItems::ActorEquippedItems()
{
	
	for (int i : Iterate(0, (int)EquippedItems::numbEquppedItems))
		m_items[(EquippedItems)i] = nullptr;

	
}


ActorEquippedItems::~ActorEquippedItems()
{
}

void ActorEquippedItems::Add(const EquippedItems & name,Item* item)
{
	m_items[name] = item;
}

Item * ActorEquippedItems::GetItem(const EquippedItems& name)
{
	if (m_items.at(name))
		return m_items[name];
	return nullptr;
}

void ActorEquippedItems::RemoveItem(const EquippedItems& name)
{
	m_items[name] = nullptr;
}
