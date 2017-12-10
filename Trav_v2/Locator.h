#pragma once
#include "Renderer.h"
#include "TextManager.h"
#include "TextureLoader.h"
class Locator
{
	static ID2D1HwndRenderTarget* rt;
	static Renderer* renderer;
	static TextManager* text;
	static ImageManager* images;
public:
	Locator();
	~Locator();
	static void SetGraphics(Renderer* r);
	static void SetRenderTarget(ID2D1HwndRenderTarget* target);
	static void SetTextManager(TextManager* t);
	static void SetImageManager(ImageManager* i);
	static ImageManager* Images();
	static  ID2D1HwndRenderTarget* RenderTarget();
	static  Renderer* Graphics();
	static TextManager* Text();
};

