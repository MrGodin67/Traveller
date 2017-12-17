#pragma once


class Level;

class LevelManager 
{
	std::vector<std::unique_ptr<Level>> m_levels;
	std::size_t m_currentLevelIndex = 0;
	Level* mp_currentLevel = nullptr;
public:
	LevelManager();
	void Initialize(const int& numbLevels, class Camera& cam);
	std::size_t LevelCount()const;
	Level& GetLevel(const std::size_t& index);
	Level& GetCurrentLevel();
	Level& SetCurrentLevel(const std::size_t& index);
	void LoadLevel(const std::size_t& level_index, class Camera& m_cam);
	~LevelManager();
};

