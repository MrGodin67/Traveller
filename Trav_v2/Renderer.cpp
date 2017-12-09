#include "stdafx.h"
#include "Renderer.h"
#include "D2DWindow.h"
#include "Locator.h"
#include <d2d1effects.h>
Renderer::Renderer()
{
	CreateDeviceIndependentResources();
	CreateDeviceResources();
}



Renderer::~Renderer()
{
	SafeRelease(&m_DefaultBrush);
	SafeRelease(&m_RenderTarget);
	SafeRelease(&m_Direct2dFactory);
}



HRESULT Renderer::BeginSceen(const RectF& color)
{
	HRESULT hr = this->CreateDeviceResources();

	if (SUCCEEDED(hr))
	{
		
		m_RenderTarget->BeginDraw();
		m_RenderTarget->Clear({ color.r,color.g,color.b,color.a });
		m_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		

	}
	return hr;
}

HRESULT Renderer::EndSceen()
{
	HRESULT hr = m_RenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		ReleaseDeviceObjects();
	}
	return hr;
}

void Renderer::DrawSprite(const D2DMatrix & trans, const D2DRectF & destRect, 
	ID2D1Bitmap * pSprite, const D2DRectF * srcRect, 
	float Opacity, D2D1_BITMAP_INTERPOLATION_MODE InterpMode)
{
	m_RenderTarget->SetTransform(trans);
	m_RenderTarget->DrawBitmap(pSprite, destRect, Opacity, InterpMode, srcRect);
}

void Renderer::RenderText(const std::wstring & text, IDWriteTextFormat * pFormat, const D2D1_RECT_F & destRect, const D2D1_COLOR_F & color, D2D1_MATRIX_3X2_F & trans)
{
	m_DefaultBrush->SetColor(color);
	m_RenderTarget->SetTransform(trans);
	m_RenderTarget->DrawTextW(text.c_str(), (UINT)text.size(), pFormat, destRect, m_DefaultBrush);
}

void Renderer::DrawRectangle(const D2DMatrix & trans, const D2DRectF & destRect, const D2D1_COLOR_F & color)
{
	m_RenderTarget->SetTransform(trans);
	m_DefaultBrush->SetColor(color);
	m_RenderTarget->DrawRectangle(destRect, m_DefaultBrush);
}

void Renderer::DrawFilledRectangle(const D2DMatrix & trans, const D2DRectF & destRect, const D2D1_COLOR_F & color)
{
	m_RenderTarget->SetTransform(trans);
	m_DefaultBrush->SetColor(color);
	m_RenderTarget->FillRectangle(destRect, m_DefaultBrush);
}

HRESULT Renderer::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_Direct2dFactory);
	Assert(hr == S_OK);
	return hr;
}

void Renderer::ReleaseDeviceObjects()
{
	SafeRelease(&m_DefaultBrush);
	SafeRelease(&m_RenderTarget);
}

HRESULT Renderer::CreateDeviceResources()
{
	HRESULT hr = S_OK;
	if (!m_RenderTarget)
	{
		
		RECT rc;

		GetClientRect(D2DWindow::WindowHandle(), &rc);

		
		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);
		
		hr = m_Direct2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(D2DWindow::WindowHandle(), size),
			&m_RenderTarget
		);
		Assert(hr == S_OK);
		if (SUCCEEDED(hr))
		{

			hr = m_RenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::White),
				&m_DefaultBrush
			);
			Assert(hr == S_OK);
		}
		Locator::SetRenderTarget(m_RenderTarget);
	}
	
	
	return hr;
}
