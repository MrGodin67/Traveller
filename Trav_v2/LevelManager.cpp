#include "stdafx.h"
#include "LevelManager.h"
#include "FileManager.h"
#include "Level.h"
#include "MapLayer.h"
#include "Camera.h"
LevelManager::LevelManager()
{
}



void LevelManager::Initialize(const int & numbLevels, Camera & cam)
{
	
}

std::size_t LevelManager::LevelCount() const
{
	return m_levels.size();
}

Level & LevelManager::GetLevel(const std::size_t & index)
{
	return static_cast<Level&>(*m_levels[index]);
}

Level & LevelManager::GetCurrentLevel()
{
	return static_cast<Level&>(*m_levels[m_currentLevelIndex]);
}

Level & LevelManager::SetCurrentLevel(const std::size_t & index)
{
	m_currentLevelIndex = index;
	
	return  GetCurrentLevel();
}

void LevelManager::LoadLevel(const std::size_t & level_index,Camera& m_cam)
{
	
	
}


LevelManager::~LevelManager()
{
}
