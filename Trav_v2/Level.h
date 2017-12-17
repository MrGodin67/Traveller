#pragma once
#include "Types.h"
#include "FileManager.h"
#include "Components.h"
#include "EntityManager.h"
const static char mapNames[10][MAX_PATH] =
{
	{ "test.bin" },
	{ "test1.bin" },
	{ "test.bin" },
	{ "test.bin" },
	{ "test.bin" },
	{ "test.bin" },
	{ "test.bin" },
	{ "test.bin" },
	{ "test.bin" },
	{ "test.bin" }
};

class Level
{
	
	int * path_map = nullptr;
	LevelData data;
	ID2D1Bitmap* m_image = nullptr;
	Vec2i worldDims;
	Vec2f cellDims;
public:
	Level();
	
	void CreateLevel(EntityManager* entMgr,const int& index);
	Vec2i MapDimensions()const;
	Vec2f CellDimensions()const;
	int * PathMap()const;
	~Level();
};

