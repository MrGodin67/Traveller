#pragma once
#include "Renderer.h"
#include "TextManager.h"
#include "TextureLoader.h"
#include "SoundManager.h"
#include "LevelManager.h"
#include "PathManager.h"

class Locator
{
	static ID2D1HwndRenderTarget* rt;
	static Renderer* renderer;
	static TextManager* text;
	static ImageManager* images;
	static SoundManager* sound;
	static LevelManager* levels;
	static class PathfindingManager* path_finder;
public:
	Locator();
	~Locator();
	static void SetGraphics(Renderer* r);
	static void SetRenderTarget(ID2D1HwndRenderTarget* target);
	static void SetTextManager(TextManager* t);
	static void SetImageManager(ImageManager* i);
	static void SetSoundManager(SoundManager* s);
	static void SetLevelManager(LevelManager* l);
	static void SetPathFinder(PathfindingManager* p);
	static ImageManager* Images();
	static  ID2D1HwndRenderTarget* RenderTarget();
	static  Renderer* Graphics();
	static TextManager* Text();
	static SoundManager* Audio();
	static LevelManager* Levels();
	static PathfindingManager* PathFinding();
};

