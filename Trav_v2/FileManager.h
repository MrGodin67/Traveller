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
	int mapLayers[2][MAX_MAP_SIZE];
	int layer_count;


};
class FileManager
{
public:
	FileManager();
	~FileManager();
	static bool ReadLevelFile(const char* path, LevelData& data);
};

