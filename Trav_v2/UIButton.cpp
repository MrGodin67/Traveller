#include "stdafx.h"
#include "UIButton.h"
#include "Locator.h"
int UIButton::m_width;
int UIButton::m_height;

UIButton::UIButton()
{
	
}

UIButton::UIButton(const int& returnAction, const std::wstring& text, const std::string& fontName)
	:IUserInterface(UI_TYPE_BUTTON,returnAction),m_text(text),m_fontName(fontName)
{

}


UIButton::~UIButton()
{
}

void UIButton::SetDimensions(const int & width, const int & height)
{
	m_width = width;
	m_height = height;
}



UIReturn UIButton::OnKeyPress(const unsigned char & key)
{
	return UIReturn();
}

void UIButton::Draw()
{
	
	if (m_mouseOver)
	{
		Locator::Graphics()->DrawFilledRectangle(D2D1::Matrix3x2F::Identity(),
			m_frame, m_mouseOverColor);
	}
	Locator::Graphics()->DrawRectangle(D2D1::Matrix3x2F::Identity(),
		m_frame, m_frameColor);

	Locator::Text()->GetFormat(m_fontName)->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	Locator::Graphics()->RenderText(
		m_text,
		Locator::Text()->GetFormat(m_fontName),
		UIRect(m_frame.left, m_frame.top + (m_height / Locator::Text()->GetFormat(m_fontName)->GetFontSize()),
		m_frame.right, m_frame.bottom) , 
		m_textColor
	);
	Locator::Text()->GetFormat(m_fontName)->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
}

void UIButton::Update(const float & dt)
{
}

void UIButton::SetAnchor(const UIPoint & pos)
{
	m_frame = UIRect((float)pos.x, (float)pos.y, (float)(pos.x + m_width), (float)(pos.y + m_height));
}

void UIButton::Enabled(const bool & val)
{
	m_enabled = true;
}

bool UIButton::Enabled() const
{
	return m_enabled;
}
