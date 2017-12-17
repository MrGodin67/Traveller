#pragma once
#include "EntityComponentSystem.h"
enum GroupLabels : std::size_t;

class EntityManager;
class MapLayer
{
	static int map_width;
	static int map_height;
	static int image_clip_size;
	static int image_draw_size;
	static int cell_width;
	static int cell_height;
	static int discard;
	static ID2D1Bitmap* image;
public:
	MapLayer();
	~MapLayer();
	static void Load(const int* map, EntityManager& manager, const GroupLabels& label);
	static void SetValues(ID2D1Bitmap* image,int map_width, int map_height, int image_clip_size, 
		int image_draw_size, int cell_width,
		int cell_height, int discard);
};

