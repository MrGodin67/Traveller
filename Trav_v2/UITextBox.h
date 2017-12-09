#pragma once
#include "IUserInterface.h"

class UITextBox :
	public IUserInterface
{
	std::wstring m_text;
	std::string m_fontName;
	bool m_centered = false;
	
	int m_width;
	int m_height;
public:
	UITextBox();
	UITextBox(const int& returnAction,const std::wstring& text, const int& width, const int& height,
		const std::string& fontName,bool centered = false);
	virtual ~UITextBox();
	
	// Inherited via IUserInterface
	virtual void Draw() override;
	virtual void Update(const float & dt) override;
	virtual void SetAnchor(const UIPoint& pos)override;
	virtual void SetText(const std::wstring& text);
	std::wstring GetText()const;
};

