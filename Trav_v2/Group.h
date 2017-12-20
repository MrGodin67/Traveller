#pragma once
#include "EntityComponentSystem.h"

class EntityManager;



class EntityComponentPred
{
	
public:
	bool operator()(Entity* ent)
	{ 
		return !ent->Active(); 
	}
};

template <typename _Type, typename _Pred>
static inline auto Remove_if(_Type begin, _Type end, _Pred func)
{
	return std::remove_if(begin, end, func);
}
class Group :
	public Entity
{
	std::vector<Entity*> m_entities;
	typedef std::vector<Entity*>::iterator m_entityItr;
	typedef std::vector<Entity*>::const_iterator m_entityConstItr;
	m_entityItr ItrStart;
	m_entityItr ItrEnd;
public:
	Group(EntityManager& manager);
	~Group();
	void AddEntity(Entity* ent);
	void RemoveEntity(Entity* ent);
};

