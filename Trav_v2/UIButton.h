#pragma once
#include "IUserInterface.h"
class UIButton :
	public IUserInterface
{
	static int m_width;
	static int m_height;
	bool m_enabled = true;
	std::wstring m_text;
	std::string m_fontName;
public:
	UIButton();
	UIButton(const int& returnAction,const std::wstring& text,const std::string& fontName);
	virtual ~UIButton();
	static void SetDimensions(const int& width, const int& height);
		// Inherited via IUserInterface
	virtual UIReturn OnKeyPress(const unsigned char & key) override;
	virtual void Draw() override;
	virtual void Update(const float & dt) override;
	virtual void SetAnchor(const UIPoint& pos)override;
	virtual void Enabled(const bool& val);
	virtual bool Enabled()const;
};

