#pragma once
// This will release images
class ImageManager
{
	std::unordered_map<std::wstring, ID2D1Bitmap*> m_images;
public:
	ImageManager();
	~ImageManager();
	ID2D1Bitmap* Load(const std::wstring& filename);
};

