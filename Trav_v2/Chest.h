#pragma once
#include "Components.h"
#include "EntityComponentSystem.h"
class EntityManager;
class Chest :
	public Entity
{
	std::vector<Entity*> m_items;
	std::size_t m_numbItems;
	std::size_t m_itemIndex = 0;
public:
	
	Chest() = default;
	~Chest();
	void Init(ID2D1Bitmap* image, const RectF& srcRect, const Vec2f& position,
		const Vec2f& size, const std::size_t& numbItems);
	std::size_t numberOfItems()const
	{
		return m_items.size();
	}
	Entity* GetItem(const std::size_t& index)
	{
		return m_items[index];
	}
	Item* AddItem(Item* item);
	
};

