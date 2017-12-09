#pragma once
#include "Components.h"
#include "ActorEquippedItems.h"
#include "ActorInventory.h"

class Actor :
	public Entity
{
	ActorEquippedItems m_equippedItems;
	ActorInventory m_inventory;
	
	float m_lightRadius = 400.0f;
public:
	Actor() = default;
	Actor(const Vec2f& position,const Vec2f& size);
	virtual ~Actor();
	virtual void Draw()override;;
	virtual void Update(const float& dt)override;
	Item* AddItem(Item& item,const EquippedItems type);
	float LightRadius()const;
	void LightRadius(const float& val);
	ActorInventory* Inventory() { return &m_inventory; }
};

