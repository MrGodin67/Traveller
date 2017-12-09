#include "stdafx.h"
#include "UISelectScreen.h"
#include "UIButton.h"
#include "Locator.h"
UISelectUser::UISelectUser()
{
}

UISelectUser::UISelectUser(const int & posX, const int & posY, const int & width, const int & height)
{
	const int rows = (height / m_cellSize);
	const int cols = (width / m_cellSize);
	m_frame = { (float)posX,(float)posY,(float)posX + (float)width,(float)posY + (float)height };
	m_grid.Resize(rows, cols);
	for (int r : Iterate(0, (int)rows))
	{
		for (int c : Iterate(0, (int)cols))
		{
			m_grid(r, c) = UIPoint(posX + (c*m_cellSize), posY + (r*m_cellSize));
		}
	}




}


UISelectUser::~UISelectUser()
{
}
UIReturn UISelectUser::OnMouseMove(const std::size_t & x, const std::size_t & y)
{
	for (auto& it : m_items)
	{
		UIReturn result = it->OnMouseMove(x, y);
	}
	return UIReturn();
}
UIReturn UISelectUser::OnMouseClick(const std::size_t & x, const std::size_t & y)
{
	for (auto& it : m_items)
	{
		UIReturn result = it->OnMouseClick(x, y);
		if (result.action != UI_RETURN_ACTION_NONE)
		{
			switch (result.id)
			{
				case UI_TYPE_LISTBOX:
				{
					m_selectedTextBox = (UITextBox*)result.data;
					
					break;
				}
				case UI_TYPE_BUTTON:
				{
					switch (result.action)
					{
					case UI_RETURN_ACTION_SELECTED:
						result.data = &m_selectedTextBox->GetText();
						return result;
						break;
					}

					break;
				}
			}
		}
		if (result.id == UI_TYPE_LISTBOX)
		{
			return result;
		}
		
			return result;
	}
	return UIReturn();
}

UIReturn UISelectUser::OnKeyPress(const unsigned char & key)
{
	for (auto& it : m_items)
	{
		UIReturn result = it->OnKeyPress(key);
		if (result.action != UI_RETURN_ACTION_NONE)
			return result;
	}
	return UIReturn();
}

void UISelectUser::Draw()
{
	Locator::Graphics()->DrawSprite(D2D1::Matrix3x2F::Identity(), m_frame, m_image);
	Locator::Graphics()->DrawRectangle(D2D1::Matrix3x2F::Identity(),
		m_frame, D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	for (auto& it : m_items)
	{
		it->Draw();
	}
}

void UISelectUser::Update(const float & dt)
{
}

IUserInterface& UISelectUser::AddItem(IUserInterface* item, const int& row, const int& col)
{

	std::unique_ptr<IUserInterface> uPtr{ item };
	m_items.emplace_back(std::move(uPtr));
	item->SetAnchor(m_grid(row, col));
	return *item;

}


