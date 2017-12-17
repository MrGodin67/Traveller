#include "stdafx.h"
#include "Locator.h"

ID2D1HwndRenderTarget* Locator::rt = nullptr;
Renderer* Locator::renderer = nullptr;
TextManager* Locator::text = nullptr;
ImageManager* Locator::images = nullptr;
SoundManager * Locator::sound = nullptr;
LevelManager* Locator::levels = nullptr;
PathfindingManager* Locator::path_finder = nullptr;
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

void Locator::SetSoundManager(SoundManager * s)
{
	sound = s;
}

void Locator::SetLevelManager(LevelManager * l)
{
	levels = l;
}

void Locator::SetPathFinder(PathfindingManager * p)
{
	path_finder = p;
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

SoundManager * Locator::Audio()
{
	return sound;
}

LevelManager * Locator::Levels()
{
	return levels;
}

PathfindingManager * Locator::PathFinding()
{
	return path_finder;
}
