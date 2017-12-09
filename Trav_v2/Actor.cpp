#include "stdafx.h"
#include "Actor.h"
#include "Locator.h"

Actor::Actor(const Vec2f& position, const Vec2f& size)
	:m_inventory(m_equippedItems,this)
{
	Add<Transform>(position, Vec2f(0.0f, 0.0f), size);
}

Actor::~Actor()
{
}

void Actor::Draw()
{
	for (int i : Iterate(0, (int)EquippedItems::numbEquppedItems))
	{
		Item* item = m_equippedItems.GetItem((EquippedItems)i);
		if (item)
		{
			Locator::Graphics()->DrawSprite(Get<Transform>().Matrix(),
				Get<Transform>().Rect().ToD2D(), item->image, &item->srcRect.ToD2D());
		}
	}
}

void Actor::Update(const float & dt)
{
	m_inventory.Refresh();
	if (Has<InputController>())
	{
		Get<InputController>().Update(dt);
		Get<Transform>().velocity = Get<InputController>().Direction();
		//Get<Transform>().velocity.Normalize();

	}
	  
	for (auto& comp : m_components)
		comp->Update(dt);
}

Item* Actor::AddItem(Item& item, const EquippedItems type)
{
	Item* i = m_inventory.Add(item);
	if (!m_equippedItems.GetItem(type))
		m_equippedItems.Add(type,i);

	return i;
}

float Actor::LightRadius() const
{
	return m_lightRadius;
}

void Actor::LightRadius(const float & val)
{
	m_lightRadius = val;
}
