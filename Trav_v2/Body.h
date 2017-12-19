#pragma once

#include "Components.h"

class Body : public Component
{
	Transform* transform;
	ID2D1Bitmap* m_image;
public:
	Body(ID2D1Bitmap* image)
		:m_image(image)
	{};
	virtual void Init()override;
	
	virtual void Draw()override;
};