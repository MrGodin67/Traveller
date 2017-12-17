#pragma once
// This will release images

class ImageManager 
{
	std::unordered_map<std::string, ID2D1Bitmap*> m_images;
public:
	ImageManager();
	~ImageManager();
	ID2D1Bitmap* Load(const std::string& name,const std::wstring& filename);
	ID2D1Bitmap* Get(const std::string& name);
};

