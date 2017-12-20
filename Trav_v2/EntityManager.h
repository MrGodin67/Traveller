#pragma once
#include "Components.h"
#include "Camera.h"


struct Partition
{
	std::vector<Entity*> items;
	RectF frame;
};
class EntityManager 
{
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groups;
	typedef std::vector<std::unique_ptr<Entity>>::iterator m_entityItr;
	typedef std::vector<std::unique_ptr<Entity>>::const_iterator m_entityConstItr;
	m_entityItr ItrStart;
	m_entityItr ItrEnd;
	Camera& m_cam;
	std::size_t  m_currentPlayer = 0;
	void FrustumCull(Entity* ent);
	void HandlePlayer(const float& dt);
	void SetIterators();
	//void PickUpItem(Entity* item, Actor* actor);
public:
	EntityManager(Camera& cam)
		:m_cam(cam)
	{
		
	}

	void Draw();
	void Update(const float& dt);
	void Refresh();
	void DestroyAll();
	void FlushAllGroups(Entity* ent);
	void AddToGroup(Entity* ent, const GroupID& id);
	void RemoveFromGroup(Entity* ent, const GroupID& id);
	std::vector<Entity*>& GetGroup(const GroupID& id);
	void AquireTarget(Entity* ent);
	
	void GetPath(Entity* ent,const Vec2f& targetPosition);
	// add / get generic entity
	Entity& Add();
	// add / get with transform
	Entity& Add(const Vec2f& pos,const Vec2f& vel, const Vec2f& size);
	template <typename Type, typename... TArgs>
	Type& Add(TArgs&&... mArgs)
	{
		Type* ent(new Type(std::forward<TArgs>(mArgs)...));
		std::unique_ptr<Type> uPtr{ ent };
		entities.emplace_back(std::move(uPtr));
		SetIterators();
		return *ent;
	}
	
	bool GetLineOfSight(const Vec2f& from,const Vec2f& to);
	//void FireAmmo(const Vec2f& position, const Vec2f& direction, const Vec2f& size,Ammo * ammo);
	void DoLight();
};