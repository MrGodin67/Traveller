#include "stdafx.h"
#include "Locator.h"

ID2D1HwndRenderTarget* Locator::rt = nullptr;
Renderer* Locator::renderer = nullptr;
TextManager* Locator::text = nullptr;
ImageManager* Locator::images = nullptr;
Locator::Locator()
{
}


Locator::~Locator()
{
}

void Locator::SetGraphics(Renderer * r)
{
	renderer = r;
}

void Locator::SetRenderTarget(ID2D1HwndRenderTarget * target)
{
	rt = target;
}

void Locator::SetTextManager(TextManager * t)
{
	text = t;
}

void Locator::SetImageManager(ImageManager * i)
{
	images = i;
}

ImageManager * Locator::Images()
{
	return images;
}

ID2D1HwndRenderTarget * Locator::RenderTarget()
{
	return rt;
}

Renderer * Locator::Graphics()
{
	return renderer;
}

TextManager * Locator::Text()
{
	return text;
}
