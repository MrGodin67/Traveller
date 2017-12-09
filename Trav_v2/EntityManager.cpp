#include "stdafx.h"
#include "EntityManager.h"
#include "Actor.h"


void EntityManager::Draw()
{
	// render by layers
	for (auto& ent : GetGroup(groupRender))ent->Draw();

	for (auto& ent : GetGroup(groupItems))ent->Draw();
	for (auto& ent : GetGroup(groupEnemies))ent->Draw();
	//for (auto& ent : GetGroup(groupPlayers))ent->Draw();
	for (auto& ent : GetGroup(groupChest))ent->Draw();



}

void EntityManager::Update(const float & dt)
{
	RectF frustum = m_cam.Frustum();
	GetGroup(groupRender).clear();
	// map first
	HandlePlayer(dt);
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
	DoLight();
}

void EntityManager::Refresh()
{
	
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
	
	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](const std::unique_ptr<Entity>& inEnt)
	{
		return !inEnt->Active();
	}), std::end(entities));
}

void EntityManager::DestroyAll()
{
	for (auto& ent : entities)
		ent->Destroy();

}

void EntityManager::FrustumCull(Entity* ent)
{
	if (ent->Get<Transform>().Rect().Overlaps(m_cam.Frustum()))
		ent->AddGroup(groupRender);
	else
		ent->RemoveGroup(groupRender);
	
}

void EntityManager::HandlePlayer(const float& dt)
{
	
	for (auto& players : GetGroup(groupPlayers))
	{
		players->Update(dt);
		for (auto& it : GetGroup(groupCollider))
		{
			
			if (it->Has<TileComp>() && it->Has<Collider>())
			{
				Collision data = players->Get<Collider>().AABBCollision(it->Get<Collider>().AABB());
				if (data.intersecting)
					players->Get<Collider>().StaticCollisionCorrection(it->Get<Collider>().AABB(), data);

			}
			/*if (it->HasGroup(groupPlayers)&& it->Has<Collider>() && it != players)
			{
				Collision data = players->Get<Collider>().AABBCollision(it->Get<Collider>().AABB());
				if (data.intersecting)
					players->Get<Collider>().MovingEntitiesCollisionCorrection(it, data);

			}*/
		}
		m_cam.UpdatePosition(GetGroup(groupPlayers)[m_currentPlayer]->Get<Transform>().Center());
		
		players->Get<Transform>().Translate(-m_cam.GetPosition());
		
	}
	
}

void EntityManager::AddToGroup(Entity * ent, const GroupID& id)
{
	groups[id].emplace_back(ent);
}

std::vector<Entity*>& EntityManager::GetGroup(const GroupID & id)
{
	
	return groups[id];
}

void EntityManager::AquireTarget(Entity * ent)
{
	
}

void EntityManager::TransformPosition(const Vec2f & offset)
{
	for (auto& it : entities)
		it->Get<Transform>().Translate(offset);
}

Entity & EntityManager::Add()
{
	Entity * ent = new Entity();
	std::unique_ptr<Entity> uPtr{ ent };
	entities.emplace_back(std::move(uPtr));
	return *ent;
}
// add with transform
Entity & EntityManager::Add( const Vec2f & pos,const Vec2f & vel,  const Vec2f & size)
{
	Entity * ent = new Entity();
	ent->Add<Transform>(pos, vel, size);
	std::unique_ptr<Entity> uPtr{ ent };
	entities.emplace_back(std::move(uPtr));
	return *ent;
}

bool EntityManager::GetLineOfSight(const Vec2f& from, const Vec2f& to)
{
	/*for (auto& it2 : GetGroup(groupRender))
	{
		if (it2->Has<Collider>())
		{
			if (Intersect::LineToBoundingBox(LineF(from, to), AABBF(it2->Get<Collider>().AABB())))
			{
				return false;
				
			};
		}
	}*/
	return true;
}

bool EntityManager::DoCollision(Entity * A,Entity * B, std::vector<RectF>& collisionRects)
{
	
		
		return false;
}

bool EntityManager::DoCollision(Entity * ent)
{
	
	return false;
}

bool EntityManager::DoCollision(Entity * ent, Collider & collider)
{
	
	return true;
}

void EntityManager::DoLight()
{
	for (auto& it : GetGroup(groupLight))
	{
		for (auto& it2 : GetGroup(groupRender))
		{
			if (it == it2)continue;
			float len = (it->Get<Transform>().Center() - it2->Get<Transform>().Center()).Len();
			float result = 1.0f - abs((len / it->Get<Light>().Range()));
			if(it2->Has<TileComp>())
			   it2->Get<TileComp>().Fade(result);
			
		}
	}
}
