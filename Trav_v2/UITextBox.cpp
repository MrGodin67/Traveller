#include "stdafx.h"
#include "UITextBox.h"
#include "Locator.h"

UITextBox::UITextBox()
{
}

UITextBox::UITextBox(const int& returnAction, const std::wstring& text, const int& width, const int& height,
	const std::string& fontName, bool centered)
	:IUserInterface(UI_TYPE_TEXTBOX,returnAction),
	m_text(text),m_fontName(fontName),m_width(width),m_height(height),m_centered(centered)
{
	
}

UITextBox::~UITextBox()
{
}







void UITextBox::Draw()
{
	if (m_mouseOver && m_showHightlight || m_selected && m_showHightlight)
	{
		Locator::Graphics()->DrawFilledRectangle(D2D1::Matrix3x2F::Identity(),
			m_frame, m_mouseOverColor);
	}
	if(m_drawFrame)
	     Locator::Graphics()->DrawRectangle(D2D1::Matrix3x2F::Identity(),
		     m_frame, m_frameColor);
	if(m_centered)
	  Locator::Text()->GetFormat(m_fontName)->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	Locator::Graphics()->RenderText(
		m_text,
		Locator::Text()->GetFormat(m_fontName),
		UIRect(m_frame.left, m_frame.top + (m_height / Locator::Text()->GetFormat(m_fontName)->GetFontSize()),
			m_frame.right, m_frame.bottom),
		m_textColor
	);
	
	if(m_centered)
	  Locator::Text()->GetFormat(m_fontName)->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
}

void UITextBox::Update(const float & dt)
{
}

void UITextBox::SetAnchor(const UIPoint & pos)
{
	m_frame = UIRect((float)pos.x, (float)pos.y, (float)pos.x + (float)m_width, (float)pos.y +(float)m_height);
}

void UITextBox::SetText(const std::wstring & text)
{
	m_text = text;
}

std::wstring UITextBox::GetText() const
{
	return m_text;
}



