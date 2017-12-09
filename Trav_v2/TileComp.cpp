#include "stdafx.h"
#include "TileComp.h"


TileComp::TileComp()
{
}

TileComp::TileComp(ID2D1Bitmap * image, const RectF & srcRect)
	:image(image),srcRect(srcRect)
{
}


TileComp::~TileComp()
{
}

void TileComp::Draw()
{
	Locator::Graphics()->DrawSprite(owner->Get<Transform>().Matrix(),
		owner->Get<Transform>().Rect().ToD2D(), image, &srcRect.ToD2D(),transparency);
}

void TileComp::Init()
{
	
}
void TileComp::Fade(const float & val)
{
	transparency = val;
}

