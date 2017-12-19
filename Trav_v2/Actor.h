#pragma once
#include "Components.h"
class Actor :
	public Entity
{
public:
	Actor() = default;
	Actor(EntityManager& manager);
	virtual ~Actor();
	virtual void Draw()override;
	virtual void Update(const float& dt)override;
};

