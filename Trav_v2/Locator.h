#pragma once
#include "Renderer.h"
#include "TextManager.h"
#include "TextureLoader.h"
#include "SoundManager.h"

#include "PathManager.h"

class Locator
{
	static ID2D1HwndRenderTarget* rt;
	static Renderer* renderer;
	static TextManager* text;
	static ImageManager* images;
	static SoundManager* sound;
	static class PathfindingManager* path_finder;
public:
	Locator();
	~Locator();
	static void SetGraphics(Renderer* r);
	static void SetRenderTarget(ID2D1HwndRenderTarget* target);
	static void SetTextManager(TextManager* t);
	static void SetImageManager(ImageManager* i);
	static void SetSoundManager(SoundManager* s);
	static void SetPathFinder(PathfindingManager* p);
	static ImageManager* Images();
	static  ID2D1HwndRenderTarget* RenderTarget();
	static  Renderer* Graphics();
	static TextManager* Text();
	static SoundManager* Audio();
	static PathfindingManager* PathFinding();
};

