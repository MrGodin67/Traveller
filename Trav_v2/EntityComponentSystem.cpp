#include "stdafx.h"
#include "EntityComponentSystem.h"
#include "EntityManager.h"
EntityManager* Entity::manager = nullptr;
void Entity::SetManager(EntityManager * mgr)
{
	manager = mgr;
}
void Entity::AddGroup(const GroupID & id)
{
	m_groupBitSet[id] = true;
	manager->AddToGroup(this, id);
}
