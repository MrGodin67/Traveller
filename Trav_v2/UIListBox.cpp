#include "stdafx.h"
#include "UIListBox.h"
#include "Locator.h"

UIListBox::UIListBox()
{
}

UIListBox::UIListBox(const int & posX, const int & posY, const int & width, const int & height,
	const int& maxItems, const int& textBoxWidth, const int& textBoxHeight)
	:UIWindow(posX,posY,width,height),m_maxItems(maxItems),m_textBoxWidth(textBoxWidth),
	m_textBoxHeight(textBoxHeight)
{
}


UIListBox::~UIListBox()
{
}

UIReturn UIListBox::OnMouseClick(const std::size_t & x, const std::size_t & y)
{
	UIReturn result;
	if (!m_frame.Contains(x, y))
		return result;// if not in this window
	
	for (int i : Iterate(0, (int)m_items.size()))
	{
		result = m_items[i]->OnMouseClick(x, y);
		if (result.action == UI_RETURN_ACTION_SELECTED)
		{
			if (m_items[i].get() != m_selectedTextBox)
			{
				if (m_selectedTextBox)
				{
					m_selectedTextBox->DrawFrame(false);
					m_selectedTextBox->Selected(false);
				}

				m_selectedTextBox = dynamic_cast<UITextBox*>(m_items[i].get());
				m_selectedTextBox->DrawFrame(true);
				result.id = UI_TYPE_LISTBOX;
				result.data = m_selectedTextBox;
				return result;
			}
			
		}

	}
	
	return UIReturn();
}

UIReturn UIListBox::OnMouseMove(const std::size_t & x, const std::size_t & y)
{
	for (int i : Iterate(0, (int)m_items.size()))
	{
		m_items[i]->OnMouseMove(x, y);
	}
	return UIReturn();
}

void UIListBox::Draw()
{
	Locator::Graphics()->DrawFilledRectangle(D2D1::Matrix3x2F::Identity(),
		m_frame, D2D1::ColorF(0.5f, 0.5f, 0.5f, 0.8f));
	Locator::Graphics()->DrawRectangle(D2D1::Matrix3x2F::Identity(),
		m_frame, D2D1::ColorF(0.0f, 1.0f, 1.5f, 1.0f));
	for (int i : Iterate(0, (int)m_items.size()))
	{
		m_items[i]->Draw();
	}
}



UITextBox & UIListBox::Add(const std::wstring & text)
{
	if (m_numbItems < m_maxItems)
	{
		UITextBox* box = new UITextBox(UI_RETURN_ACTION_SELECTED, text, m_textBoxWidth,
			m_textBoxHeight, "Tahoma10", true);
		box->ShowHightlight(true);
		AddItem(box, m_startY, m_startX);
		m_startY++;
		m_numbItems++;

		return *box;
	}
}

void UIListBox::SetAnchor(const UIPoint & pos)
{
}
