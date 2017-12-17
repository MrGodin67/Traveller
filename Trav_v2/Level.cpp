#include "stdafx.h"
#include "Level.h"
#include "EntityManager.h"
#include "Camera.h"
Level::Level()
{
}



void Level::CreateLevel(EntityManager* entMgr, const int& index)
{
	
	FileManager::ReadLevelFile(mapNames[index], data);
	m_image = Locator::Images()->Load("m1F", data.image_path);
	Assert(m_image);
	worldDims = { data.width,data.height };
	cellDims = { (float)data.cell_width,(float)data.cell_height };
	int columns = (int)m_image->GetSize().width / data.image_size;// data.cell_width;
	Vec2f position = { 0.0f,0.0f };
	// the tags in data.map are relative to where they
	// are in the bitmap
	const Vec2f velocity = { 0.0f,0.0f };// no velocitiy
	const Vec2f size((float)data.image_size, (float)data.image_size);
	GroupID groupTag;
	int columnsP = data.width / 6;
	int rowsP = data.height / 6;
	int * map = nullptr;
	path_map = new int(data.width*data.height);
	for (int i : Iterate(0, data.layer_count))
	{

		switch (i)
		{
		case 0:
			groupTag = groupMapLayer1;
			
			break;
		case 1:
			groupTag = groupMapLayer2;
			break;
		}
		map = data.mapLayers[i];
		for (int r : Iterate(0, data.height))
		{
			position.x = 0.0f;
			for (int c : Iterate(0, data.width))
			{
				// get value at map index
				const int index = r *  data.width + c;
				int mapTag = map[index];
				if (mapTag != -1)
				{

					// get where we are on the image to make a clipping rectangle
					float x = (float)(mapTag % columns) * (float)data.cell_width;// data.cell_width;
					float y = (float)(mapTag / columns) * (float)data.cell_height;// data.cell_height;
					RectF sourceRect = { x,y,x + (float)data.cell_width,y + (float)data.cell_height };
					// create entity with a transform


					// add colliders where needed
					switch (groupTag)
					{
					case groupMapLayer1:
					{
						switch (mapTag)
						{
						case 4:
						case 7:
						{
							Entity* tile = &entMgr->Add(position, velocity, size);

							// add tile component
							tile->Add<TileComp>(m_image, sourceRect);
							// add to map group			
							tile->AddGroup(groupTag);
							Collider* c = &tile->Add<Collider>((position + -(size * 0.5f)), size * 0.5f);
							// used for debug purpose
							c->doDraw = false;
							tile->AddGroup(groupCollider);
							path_map[index] = 0;
							break;
						}
						default:
							Entity* tile = &entMgr->Add(position, velocity, size);

							// add tile component
							tile->Add<TileComp>(m_image, sourceRect);
							// add to map group			
							tile->AddGroup(groupTag);
							path_map[index] = 1;
							break;
						}
					}
					break;
					case groupMapLayer2:
					{
						switch (mapTag)
						{

						case 42://potion
						{
							break;
						}
						case 37://chest
						{
							break;
						}
						default:
							Entity* tile = &entMgr->Add(position, velocity, size);

							// add tile component
							tile->Add<TileComp>(m_image, sourceRect);
							// add to map group			
							tile->AddGroup(groupTag);
							break;
						}
					}
					break;

					}

				}

				// increment along columns
				position.x += (float)data.cell_width;
			}
			// increment row
			position.y += (float)data.cell_height;
		}
	}
	
}



Vec2i Level::MapDimensions() const
{
	return worldDims;
}

Vec2f Level::CellDimensions() const
{
	return cellDims;
}

int * Level::PathMap()const
{
	return path_map;
}


Level::~Level()
{
	SafeDeleteArray(&path_map);
}
