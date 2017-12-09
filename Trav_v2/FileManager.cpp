#include "stdafx.h"
#include "FileManager.h"


FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}

bool FileManager::ReadLevelFile(const char * path, LevelData & data)
{
	FILE* file;
	fopen_s(&file, path, "rb");
	std::size_t bytes;
	if (file)
	{
		bytes = fread(&data, sizeof(LevelData), 1, file);
		if (bytes == 0)
		{
			fclose(file);
			Assert(bytes == 0);
			return false;
		}

	}
	else
	{
		return false;
	}
	fclose(file);
	return true;
}
