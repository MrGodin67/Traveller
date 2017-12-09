#include "stdafx.h"
#include "ViewPort.h"

#include "Locator.h"
ViewPort::ViewPort( Vec2f & vp_size, Vec2f & windowSize)
{
	float left = (windowSize.x * 0.5f) - (vp_size.x * 0.5f);
	float top = (windowSize.y * 0.5f) - (vp_size.y * 0.5f);
	m_view = { left,top,left + vp_size.width,top + vp_size.height };
	Locator::RenderTarget()->CreateLayer(NULL, &pLayer);
	
	
}

ViewPort::~ViewPort()
{
	SafeRelease(&pLayer);
}



float ViewPort::Width()
{
	return m_view.right - m_view.left;
}

float ViewPort::Height()
{
	return m_view.bottom - m_view.top;
}

RectF ViewPort::GetViewRect()
{
	return m_view;
}

Vec2f ViewPort::GetViewTopLeft()
{
	return{ m_view.left,m_view.top };
}

void ViewPort::BeginScene(ID2D1Brush * brush)

{
	
	Locator::RenderTarget()->PushLayer(	D2D1::LayerParameters(
			m_view.ToD2D(),NULL,D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
			D2D1::Matrix3x2F::Identity(), m_transparency,brush,D2D1_LAYER_OPTIONS_NONE),
			pLayer);


}

void ViewPort::EndScene()
{
	Locator::RenderTarget()->PopLayer();
	
}

void ViewPort::ResetTransparency()
{
	m_transparency = 0.0f;
}
