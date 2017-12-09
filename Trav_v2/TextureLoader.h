#pragma once
// This will release images
class TextureLoader
{
	static std::unordered_map<std::wstring, ID2D1Bitmap*> m_images;
public:
	TextureLoader();
	~TextureLoader();
	static ID2D1Bitmap* Load(const std::wstring& filename);
};

