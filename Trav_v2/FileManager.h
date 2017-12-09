#pragma once

#define MAX_MAP_SIZE 80 * 80
struct LevelData
{
	int width;
	int height;
	int cell_width;
	int cell_height;
	int enemy_count;
	int weapons_count;
	int armor_count;
	int potion_count;
	int level_index;
	int image_size;
	float back_color[4];
	wchar_t image_path[MAX_PATH];
	int mapLayer1[MAX_MAP_SIZE];
	int mapLayer2[MAX_MAP_SIZE];


};
class FileManager
{
public:
	FileManager();
	~FileManager();
	static bool ReadLevelFile(const char* path, LevelData& data);
};

