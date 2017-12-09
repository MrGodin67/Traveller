#pragma once
#include "Renderer.h"
#include "TextManager.h"
class Locator
{
	static ID2D1HwndRenderTarget* rt;
	static Renderer* renderer;
	static TextManager* text;
public:
	Locator();
	~Locator();
	static void SetGraphics(Renderer* r);
	static void SetRenderTarget(ID2D1HwndRenderTarget* target);
	static void SetTextManager(TextManager* t);
	static  ID2D1HwndRenderTarget* RenderTarget();
	static  Renderer* Graphics();
	static TextManager* Text();
};

