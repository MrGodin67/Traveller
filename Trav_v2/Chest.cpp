#include "stdafx.h"
#include "Chest.h"
#include "EntityManager.h"






Chest::~Chest()
{
}

void Chest::Init(ID2D1Bitmap * image, const RectF & srcRect, const Vec2f & position, const Vec2f & size, const std::size_t & numbItems)
{
	m_items.resize(numbItems);
	for (int i : Iterate(0, numbItems))
	{
		m_items[i] = &manager->Add(position, Vec2f(0.0f, 0.0f), size);
		
	}

	Add<Transform>(position, Vec2f(0.0f, 0.0f), size);
	Add<Sprite>(*image, srcRect);
	AddGroup(groupChest);
}

Item * Chest::AddItem(Item * item)
{
	
    Add<Item>(*item);
	return item;
}


