#include "stdafx.h"
#include "PathManager.h"
#include "Components.h"
#include "newAStar.h"
MyAStar* PathfindingManager::m_pathFinder = nullptr;
std::mutex PathfindingManager::lk1;
//std::mutex PathfindingManager::lk2;

// function for thread
 std::vector<Vec2f> PathfindingManager::_getPath(const Vec2f& start, const Vec2f& end)
{
	 //std::lock(lk1);
	 lk1.lock();
	 std::vector<Vec2f> path  =  m_pathFinder->getPath(start, end);
	 lk1.unlock();
	 //lk2.unlock();
	 return path;
}

 void PathfindingManager::removeFromQueue(int & index)
 {
	 if (m_queue[index])
		 delete m_queue[index];

	 m_queue.erase(m_queue.begin() + index);
	 index--;
 }

 PathfindingManager::PathfindingManager()
 {
	
 }

 PathfindingManager::~PathfindingManager()
{
	SafeDelete(&m_pathFinder );

	for (auto& it : m_queue)
		SafeDelete(&it);
}



void PathfindingManager::Initialize(const int * map, const Vec2i & worldDims, const Vec2f & celldims)
{
	SafeDelete(&m_pathFinder);
	m_pathFinder = new MyAStar(worldDims, celldims);
	for (int r : Iterate(0, worldDims.y))
	{
		for (int c : Iterate(0, worldDims.x))
		{
			const int index = r * worldDims.x + c;
			newNode* n = new newNode(map[index] != 0);
			n->gridRow = r;
			n->gridCol = c;
			m_pathFinder->setNode(n);
		}
	}
	
}
void PathfindingManager::setNode(newNode* node)
{
	m_pathFinder->setNode(node);
}

void PathfindingManager::requestPath(const Vec2f& start, const Vec2f& end,Entity * owner)
{
	
	PathRequest* req = new PathRequest();
	req->thread = std::async(_getPath, start, end);
	req->owner = owner;
	m_queue.push_back(req);
	

}

void PathfindingManager::checkForDone()
{
	if (m_queue.size() == 0)return;
	for (int i = 0; i < m_queue.size(); i++)
	{
		if (m_queue[i]->thread.valid())
		{
			std::vector<Vec2f> p = m_queue[i]->thread.get();
			if (p.size() > 0 )
			{
				m_queue[i]->owner->Add<Path>(p);
				m_queue[i]->owner->AddGroup(groupPathFollowing);
				removeFromQueue(i);
			}
		}
	}
}
