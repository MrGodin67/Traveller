#pragma once
#include "Utils2D_v2.h"

class Renderer 
{
	ID2D1Factory* m_Direct2dFactory = nullptr;
	ID2D1HwndRenderTarget* m_RenderTarget = nullptr;
	ID2D1SolidColorBrush* m_DefaultBrush = nullptr;
	
	HRESULT CreateDeviceResources();
	HRESULT CreateDeviceIndependentResources();
	void ReleaseDeviceObjects();
	
public:
	Renderer();
	
	~Renderer();
	
	HRESULT BeginSceen(const RectF& color);
	HRESULT EndSceen();
	void DrawSprite(const D2DMatrix &trans, const D2DRectF &destRect, ID2D1Bitmap *pSprite,
		const D2DRectF *rcRect = nullptr, float Opacity = 1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE InterpMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	void RenderText(const std::wstring& text, IDWriteTextFormat *pFormat,
		const D2D1_RECT_F &destRect, const D2D1_COLOR_F &color, D2D1_MATRIX_3X2_F &trans = D2D1::Matrix3x2F::Identity());
	void DrawRectangle(const D2DMatrix & trans, const D2DRectF & destRect, const D2D1_COLOR_F & color);
	void DrawLine(const D2DMatrix & trans, const D2DPointF * points, const D2D1_COLOR_F & color);
	void DrawFilledRectangle(const D2DMatrix & trans, const D2DRectF & destRect, const D2D1_COLOR_F & color);
};

