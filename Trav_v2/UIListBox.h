#pragma once
#include "UI.h"
class UIListBox :
	public UIWindow
{
	int m_numbItems = 0;
	int m_maxItems = 0;
	int m_textBoxWidth;
	int m_textBoxHeight;
	int m_startX = 0;
	int m_startY = 0;
	UITextBox* m_selectedTextBox = nullptr;
public:
	UIListBox();
	UIListBox(const int& posX, const int& posY, const int& width, const int& height,
		const int& maxItems,const int& textBoxWidth,const int& textBoxHeight);
	virtual ~UIListBox();
	virtual UIReturn OnMouseClick(const std::size_t & x, const std::size_t & y) override;
	virtual UIReturn OnMouseMove(const std::size_t & x, const std::size_t & y) override;
	virtual void Draw() override;
	UITextBox& Add( const std::wstring& text );
	virtual void SetAnchor(const UIPoint& pos)override;

};

