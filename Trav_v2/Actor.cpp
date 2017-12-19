#include "stdafx.h"
#include "Actor.h"


Actor::Actor(EntityManager& manager)
	:Entity(manager)
{
}


Actor::~Actor()
{
}

void Actor::Draw()
{
	for (auto& component : m_components)
	{
		component->Draw();
	}
}

void Actor::Update(const float & dt)
{
	
	
	for (auto& component : m_components)
	{
		
		component->Update(dt);
	}
}
