#include "stdafx.h"
#include "TextManager.h"


IDWriteTextFormat * TextManager::CreateFormat(LPWSTR FontName, float FontSize, DWRITE_FONT_WEIGHT FontWeight, DWRITE_FONT_STYLE FontStyle, DWRITE_FONT_STRETCH FontStretch, LPWSTR FontLocale)
{
	IDWriteTextFormat *pFormat = nullptr;
	HRESULT hr = pFactory->CreateTextFormat(FontName, nullptr, FontWeight, FontStyle,
		FontStretch, FontSize, FontLocale, &pFormat);

	return pFormat;
}

TextManager::TextManager()
{
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
		(IUnknown**)(&pFactory));
}


TextManager::~TextManager()
{
	SafeRelease(&pFactory);
	for (auto it : m_Fonts)
		SafeRelease(&it.second);
}

bool TextManager::InitializeFont(const std::string & fontTitle, const FontPair & desc)

{
	m_Fonts[fontTitle] = CreateFormat(const_cast<LPWSTR>(desc.first.c_str()), desc.second);
	if (!m_Fonts[fontTitle]) { return false; }
	return true;
}

IDWriteTextFormat * TextManager::GetFormat(const std::string & fontTitle)
{
	return m_Fonts[fontTitle];
}
