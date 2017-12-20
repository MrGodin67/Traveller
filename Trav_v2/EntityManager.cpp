#include "stdafx.h"
#include "EntityManager.h"


#include "Locator.h"
void EntityManager::Draw()
{
	// render by layers
	//for (auto& ent : GetGroup(groupMapLayer1))ent->Draw();
	for (auto& ent : GetGroup(groupRender))ent->Draw();
	for (auto& ent : GetGroup(groupItems))ent->Draw();
	for (auto& ent : GetGroup(groupEnemies))ent->Draw();
	//for (auto& ent : GetGroup(groupPlayers))ent->Draw();
	



}

void EntityManager::Update(const float & dt)
{
	for (auto& ent : GetGroup(groupPathFollowing))
	{
		if (ent->Get<Path>().Completed())
		{
			ent->RemoveGroup(groupPathFollowing);
			ent->Remove<Path>();
		}
	}
	GetGroup(groupRender).clear();
	// map first
	HandlePlayer(dt);
	for (auto& ent : GetGroup(groupChest))
	{
		ent->Update(dt);
		ent->Get<Transform>().Translate(-m_cam.GetPosition());
		FrustumCull(ent);
	}
	for (auto& ent : GetGroup(groupMapLayer1))
	{
		ent->Update(dt);
		ent->Get<Transform>().Translate(-m_cam.GetPosition());
		FrustumCull(ent);
	}
	// items on map
	for (auto& ent : GetGroup(groupMapLayer2))
	{
		ent->Update(dt);
		ent->Get<Transform>().Translate(-m_cam.GetPosition());
		FrustumCull(ent);
	}
	// players
	for (auto& ent : GetGroup(groupPlayers))
	{
	
		FrustumCull(ent);
	}
	
	// TO DO:
	// enemies
	// 
	//DoLight();
}

void EntityManager::Refresh()
{
	SetIterators();
	for (auto i(0u); i < maxGroups; i++)
	{
		auto& v(groups[i]);
		v.erase(std::remove_if(std::begin(v),std::end(v),
			[i](Entity* ent)
		{
			return !ent->Active() || !ent->HasGroup(i);
		}
		), std::end(v));
	}
	if(!entities.empty())
	   entities.erase(std::remove_if(ItrStart,ItrEnd,EntityActive()), ItrEnd);
}

void EntityManager::DestroyAll()
{
	for (auto& ent : entities)
		ent->Destroy();

}

void EntityManager::FlushAllGroups(Entity * ent)
{
	for (int i : Iterate(0, (int)groupNumGroups))
	{
		RemoveFromGroup(ent, (GroupLabels)i);
	}
}

void EntityManager::FrustumCull(Entity* ent)
{
	if (ent->Get<Transform>().Rect().Overlaps(m_cam.Frustum()))
		ent->AddGroup(groupRender);
	
	
}

void EntityManager::HandlePlayer(const float& dt)
{
	
	for (auto& players : GetGroup(groupPlayers))
	{
		players->Update(dt);
			for (auto& it : GetGroup(groupCollider))
		{
			
				for (auto& ent : GetGroup(groupAmmo))
				{
					if (it->Has<TileComp>())
					{
						Collision data = ent->Get<Collider>().AABBCollision(it->Get<Collider>().AABB());
						if (data.intersecting)
						{
							
							ent->Destroy();
						}


					}
				}
				
			Collision data = players->Get<Collider>().AABBCollision(it->Get<Collider>().AABB());
			if (data.intersecting)
			{
				if (it->HasGroup(groupItems))
				{
					
					//PickUpItem(it, (Actor*)GetGroup(groupPlayers)[m_currentPlayer]);
				
					return;
				}
				

				if (it->Has<TileComp>())
				{
					Collision data = players->Get<Collider>().AABBCollision(it->Get<Collider>().AABB());
					if (data.intersecting)
						players->Get<Collider>().StaticCollisionCorrection(it->Get<Collider>().AABB(), data);

				}
			}

			
			
		}
		m_cam.UpdatePosition(GetGroup(groupPlayers)[m_currentPlayer]->Get<Transform>().Center());
		players->Get<Turret>().Translate(-m_cam.GetPosition());
		players->Get<Transform>().Translate(-m_cam.GetPosition());
		
	}
	
}

void EntityManager::SetIterators()
{
	ItrStart = entities.begin();
	ItrEnd = entities.end();
}

//void EntityManager::PickUpItem(Entity * item, Actor * actor)
//{
//	RemoveFromGroup(item, groupItems);
//	RemoveFromGroup(item, groupMapLayer2);
//	RemoveFromGroup(item, groupCollider);
//	actor->AddToInventory(item);
//}

void EntityManager::AddToGroup(Entity * ent, const GroupID& id)
{
	groups[id].emplace_back(ent);
}

void EntityManager::RemoveFromGroup(Entity * ent, const GroupID & id)
{
	groups[id].erase(std::remove_if(std::begin(groups[id]), std::end(groups[id]),
		[=](Entity* groupEnt)
	{
		if (ent == groupEnt)
		{
			ent->RemoveGroup(id);
			return true;
		}
		return false;
	}), std::end(groups[id]));
}

std::vector<Entity*>& EntityManager::GetGroup(const GroupID & id)
{
	
	return groups[id];
}

void EntityManager::AquireTarget(Entity * ent)
{
	
}



void EntityManager::GetPath(Entity * ent, const Vec2f & targetPosition)
{
	Locator::PathFinding()->requestPath(ent->Get<Transform>().Center(), targetPosition, ent);
}

Entity & EntityManager::Add()
{
	Entity * ent = new Entity(*this);
	std::unique_ptr<Entity> uPtr{ ent };
	entities.emplace_back(std::move(uPtr));
	SetIterators();
	return *ent;
}
// add with transform
Entity & EntityManager::Add( const Vec2f & pos,const Vec2f & vel,  const Vec2f & size)
{
	Entity * ent = new Entity(*this);
	ent->Add<Transform>(pos, vel, size);
	std::unique_ptr<Entity> uPtr{ ent };
	entities.emplace_back(std::move(uPtr));
	SetIterators();
	return *ent;
}

bool EntityManager::GetLineOfSight(const Vec2f& from, const Vec2f& to)
{
	for (auto& it2 : GetGroup(groupRender))
	{
		if (it2->Has<TileComp>() && it2->Has<Collider>())
		{
			if (Intersect::LineToBoundingBox(LineF(from, to), AABBF(it2->Get<Transform>().Rect())))
			{
				return false;
				
			};
		}
	}
	return true;
}

//void EntityManager::FireAmmo(const Vec2f& position, const Vec2f& direction, const Vec2f& size, Ammo * ammo)
//{
//	Entity* a = &Add(position, direction, size);
//	a->Add<Collider>(position + (size * 0.5f), size * 0.5f);
//	a->Add<Sprite>(*Locator::Images()->Load("Spoof",L"assets\\spoof.png"), RectF(14.0f, 14.0f, 18.0f, 18.0f));
//	a->Add<Ammo>(*ammo);
//	a->AddGroup(groupMapLayer2);
//	a->AddGroup(groupAmmo);
//}


void EntityManager::DoLight()
{
	for (auto& it : GetGroup(groupLight))
	{
		for (auto& it2 : GetGroup(groupRender))
		{
			if (it == it2)continue;
			float len = (it->Get<Transform>().Center() - it2->Get<Transform>().Center()).Len();
			float result = 1.0f - abs((len / it->Get<Light>().Range()));
			it2->DiffuseAlpha(result);
			
		}
	}
}
