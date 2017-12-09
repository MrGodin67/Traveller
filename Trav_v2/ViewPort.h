#pragma once

#include "Utils2D_v2.h"


class ViewPort 
{
	RectF m_view;
	ID2D1Layer *pLayer = nullptr;
	float m_transparency = 1.0f;
public :
	ViewPort() = default;
	ViewPort( Vec2f& vp_size, Vec2f& windowSize);
	~ViewPort();
	
	float Width();
	float Height();
	RectF GetViewRect();
	Vec2f GetViewTopLeft();
	void BeginScene(ID2D1Brush* brush);
	void EndScene();
	void ResetTransparency();
	 
};