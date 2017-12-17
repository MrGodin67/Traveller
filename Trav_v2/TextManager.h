#pragma once
#pragma comment(lib, "dwrite.lib")
#include "system.h"
using FontPair = std::pair<std::wstring, float>;
using FontMap  =  std::unordered_map<std::string, IDWriteTextFormat*> ;
class TextManager 
{
	IDWriteFactory *pFactory;
	IDWriteTextFormat *CreateFormat(LPWSTR FontName, float FontSize,
		DWRITE_FONT_WEIGHT FontWeight = DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE FontStyle = DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH FontStretch = DWRITE_FONT_STRETCH_NORMAL,
		LPWSTR FontLocale = L"en-us");
	FontMap m_Fonts;
public:
	TextManager();
	~TextManager();
	bool InitializeFont(const std::string& fontTitle, const FontPair& desc);
	IDWriteTextFormat* GetFormat(const std::string& fontTitle);
};

