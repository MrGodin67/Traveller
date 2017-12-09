#pragma once
#include "UI.h"
class UserInterfaceManager
{

	std::unordered_map<std::string, IUserInterface*> m_windows;
	std::unique_ptr<UISelectUser> m_SelectWindow;
	std::unique_ptr<UIStartScreen> m_StartWindow;
	UIListBox* m_SelectWindowListBox = nullptr;
	IUserInterface* m_currentWindow = nullptr;
	IUserInterface* m_previousWindow = nullptr;
	
	void SetUpSelectWindow();
	void SetUpStartWindow();
	void CenterUIObject(const int& width, const int& height, int& resultX, int& resultY);
public:
	UserInterfaceManager();
	~UserInterfaceManager();
	UIReturn OnMouseClick(const std::size_t& x, const std::size_t& y);
	UIReturn OnMouseMove(const std::size_t& x, const std::size_t& y);
	UIReturn OnKeyPress(const unsigned char& key);;
	void Draw();
	void Update(const float& dt) {};
	void SetCurrentWindow(const std::string& name);
};

