#include "stdafx.h"
#include "Group.h"
#include "EntityManager.h"

Group::Group(EntityManager& manager)
	:Entity(manager)
{
	
}


Group::~Group()
{
}

void Group::AddEntity(Entity * ent)
{
	ent->Destroy();
	m_entities.push_back(ent);
	ItrStart = m_entities.begin();
	ItrEnd = m_entities.end();
	RemoveEntity(this);
	

}

void Group::RemoveEntity(Entity * ent)
{
	
}
