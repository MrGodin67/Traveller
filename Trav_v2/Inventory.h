#pragma once
#include "Components.h"
class Inventory :
	public Component
{
	std::vector<Entity*> m_items;
	std::size_t maxItems;
public:
	Inventory();
	Inventory(const std::size_t& maxItems)
		:maxItems(maxItems)
	{}
	~Inventory();
	Entity* AddItem(Entity* item)
	{
		if (m_items.size() < maxItems)
			m_items.push_back(item);
		return item;
	}
	std::size_t Count() { return m_items.size(); }
	void Remove(Entity* item)
	{
		m_items.erase(std::remove_if(m_items.begin(), m_items.end(),
			[=](Entity* ent) 
		{
			return ent == item;
		}), m_items.end());
	}
	void Refresh()
	{
		m_items.erase(std::remove_if(m_items.begin(), m_items.end(),
			[=](Entity* ent)
		{
			return !ent->Active();
		}), m_items.end());
	}
	void Update(const float& dt)override
	{
		Refresh();
		
		for (int i : Iterate(0, (int)m_items.size()))
		{
			m_items[i]->Get<Transform>().position = owner->Get<Transform>().position;
			
			  m_items[i]->Get<Transform>().Rotate(owner->Get<Transform>().angle);
		}
	}
	Entity* GetItem(const std::size_t& index)
	{
		assert(index >= 0 && index < m_items.size());
		return m_items[index];
	}
	
};

