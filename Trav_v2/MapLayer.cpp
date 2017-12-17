#include "stdafx.h"
#include "MapLayer.h"
#include "EntityManager.h"


 int MapLayer::map_width;
 int MapLayer::map_height;
 int MapLayer::image_clip_size;
 int MapLayer::image_draw_size;
 int MapLayer::cell_width;
 int MapLayer::cell_height;
 int MapLayer::discard;
 ID2D1Bitmap* MapLayer::image;
MapLayer::MapLayer()
{
}


MapLayer::~MapLayer()
{
}

void MapLayer::Load(const int * map, EntityManager & manager, const GroupLabels & label)
{
	int columns = (int)image->GetSize().width / image_clip_size;// data.cell_width;
	Vec2f position = { 0.0f,0.0f };
	// the tags in data.map are relative to where they
	// are in the bitmap
	const Vec2f velocity = { 0.0f,0.0f };// no velocitiy
	const Vec2f size((float)image_draw_size, (float)image_draw_size);
	int sizeT = sizeof(&map) / sizeof(int);
	int columnsP = map_height /6;
	int rowsP = map_width / 6;
	for (int r : Iterate(0, map_height))
	{
		position.x = 0.0f;
		for (int c : Iterate(0, map_width))
		{
			// get value at map index
			int mapTag = map[r *  map_width + c];
			if (mapTag != discard)
			{
			
				// get where we are on the image to make a clipping rectangle
				float x = (float)(mapTag % columns) * (float)image_clip_size;// data.cell_width;
				float y = (float)(mapTag / columns) * (float)image_clip_size;// data.cell_height;
				RectF sourceRect = { x,y,x + (float)image_clip_size,y + (float)image_clip_size };
				// create entity with a transform
				
				
				// add colliders where needed
				switch (label)
				{
				case groupMapLayer1:
				{
					switch (mapTag)
					{
					case 4:
					case 7:
					{
						Entity* tile = &manager.Add(position, velocity, size);

						// add tile component
						tile->Add<TileComp>(image, sourceRect);
						// add to map group			
						tile->AddGroup(label);
						Collider* c = &tile->Add<Collider>((position + -(size * 0.5f)), size * 0.5f);
						// used for debug purpose
						c->doDraw = false;
						tile->AddGroup(groupCollider);
						break;
					}
					default:
						Entity* tile = &manager.Add(position, velocity, size);

						// add tile component
						tile->Add<TileComp>(image, sourceRect);
						// add to map group			
						tile->AddGroup(label);
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
						Entity* tile = &manager.Add(position, velocity, size);

						// add tile component
						tile->Add<TileComp>(image, sourceRect);
						// add to map group			
						tile->AddGroup(label);
						break;
					}
				}
				break;

				}
				
			}
			
			// increment along columns
			position.x += (float)cell_width;
		}
		// increment row
		position.y += (float)cell_height;
	}
	
}

void MapLayer::SetValues(ID2D1Bitmap* _image,int _map_width, int _map_height, int _image_clip_size, int _image_draw_size, int _cell_width, int _cell_height, int _discard)
{
	image = _image;
	map_width = _map_width;
	map_height = _map_height;
	image_clip_size = _image_clip_size;
	image_draw_size = _image_draw_size;
	cell_width = _cell_width;
    cell_height = _cell_height;
	discard = _discard;
}
