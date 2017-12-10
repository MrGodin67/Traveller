#include "stdafx.h"
#include "UserInterfaceManager.h"
#include "D2DWindow.h"
#include "Locator.h"
void UserInterfaceManager::SetUpSelectWindow()
{
	
	int placeX, placeY;
	this->CenterUIObject(512, 512, placeX, placeY);
	m_SelectWindow = std::make_unique<UISelectUser>(placeX, placeY, 512, 512);
	m_SelectWindow->SetImage(Locator::Images()->Load(L"assets\\window.png"));
	m_SelectWindow->AddItem(new UIButton(UI_RETURN_ACTION_USER_SELECTED, L"Select", "Tahoma14"), 32 - 5, 4);
	m_SelectWindow->AddItem(new UIButton(UI_RETURN_ACTION_BACK, L"Back", "Tahoma14"), 32 - 5, 32 - 8);
	m_SelectWindow->AddItem(new UITextBox(UI_RETURN_ACTION_NONE, L"Select User", 512 - (16 * 6), 200, "Tahoma22", true), 3, 3);
	m_SelectWindowListBox = (UIListBox*)&m_SelectWindow->AddItem(new UIListBox(placeX + (16 * 8), placeY + (16 * 8), 255, 16 * 10, 10, 255, 16), 2, 2);
	m_windows["select_user"] = m_SelectWindow.get();
	

}

void UserInterfaceManager::SetUpStartWindow()
{
	int placeX, placeY;
	this->CenterUIObject(512, 512, placeX, placeY);
	m_StartWindow = std::make_unique<UIStartScreen>(placeX, placeY, 512, 512);
	m_StartWindow->SetImage(Locator::Images()->Load(L"assets\\window.png"));
	m_StartWindow->AddItem(new UIButton(UI_RETURN_ACTION_CONTINUE, L"Continue", "Tahoma14"), 32 - 5, 4);
	m_StartWindow->AddItem(new UIButton(UI_RETURN_ACTION_NEW_GAME, L"New", "Tahoma14"), 32 - 5, 4 + 5);
	m_StartWindow->AddItem(new UIButton(UI_RETURN_ACTION_EXIT, L"Exit", "Tahoma14"), 32 - 5, 32 - 8);
	m_StartWindow->AddItem(new UITextBox(UI_RETURN_ACTION_NONE, L"Traveller\nWelcome to your worst best experience", 512 - (16 * 6), 200, "Tahoma22", true), 3, 3);

	m_windows["start"] = m_StartWindow.get();
}

void UserInterfaceManager::CenterUIObject(const int & width, const int & height, int & resultX, int & resultY)
{
		size_t scrnW = D2DWindow::ScreenWidth();
		size_t scrnH = D2DWindow::ScreenHeight();
		resultX = (int)(scrnW / 2) - (width / 2);
		resultY = (int)(scrnH / 2) - (height / 2);
}

UserInterfaceManager::UserInterfaceManager()
{
	UIButton::SetDimensions(64, 24);
	IUserInterface::SetColors(UIColor(1.0f, 1.0f, 1.0f, 1.0f), UIColor(0.25f, 0.25f, 1.00f, 0.25f), UIColor(1.0f, 1.0f, 1.0f, 1.0f));
	SetUpStartWindow();
	SetUpSelectWindow();
}


UserInterfaceManager::~UserInterfaceManager()
{
}

UIReturn UserInterfaceManager::OnMouseClick(const std::size_t & x, const std::size_t & y)
{
	
	UIReturn result = m_currentWindow->OnMouseClick(x, y);
	switch (result.id)
	{
	case UI_TYPE_BUTTON:
	{
		switch (result.action)
		{
		case UI_RETURN_ACTION_CONTINUE:
			m_previousWindow = m_currentWindow;
			m_currentWindow = m_windows["select_user"];
			break;
		case UI_RETURN_ACTION_BACK:
			m_currentWindow = m_previousWindow;
			break;
		case UI_RETURN_ACTION_USER_SELECTED:
			return result;
			break;
		}
		break;
	}
	}
	return UIReturn();
}

UIReturn UserInterfaceManager::OnMouseMove(const std::size_t & x, const std::size_t & y)
{
	m_currentWindow->OnMouseMove(x, y);
	return UIReturn();
}

UIReturn UserInterfaceManager::OnKeyPress(const unsigned char & key)
{
	return UIReturn();
}

void UserInterfaceManager::Draw()
{
	m_currentWindow->Draw();
}

void UserInterfaceManager::SetCurrentWindow(const std::string & name)
{
	m_previousWindow = m_currentWindow;
	m_currentWindow = m_windows[name];
}
