#include "stdafx.h"
#include "EntityComponentSystem.h"
#include "EntityManager.h"


void Entity::DiffuseAlpha(const float & val)
{
	for (auto& it : m_components)
		it->Fade(val);
}
void Entity::AddGroup(const GroupID & id)
{
	
	
	m_groupBitSet[id] = true;
	manager.AddToGroup(this, id);
}
