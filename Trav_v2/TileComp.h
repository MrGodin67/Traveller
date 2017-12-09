#pragma once
#include "Components.h"

class TileComp :
	public Component
{
	ID2D1Bitmap* image;
	RectF srcRect;
	float transparency;
public:
	TileComp();
	TileComp(ID2D1Bitmap* image, const RectF& srcRect);
	~TileComp();
	virtual void Draw()override;
	virtual void Init()override;
	void Fade(const float& val)override;
	
	
};

